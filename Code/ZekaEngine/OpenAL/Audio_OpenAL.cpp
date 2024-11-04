#include "Audio_OpenAL.h"

ZK_NAMESPACE_BEGIN

ALenum GetOpenALFormat(uint32 bytesPerSample, uint32 numChannels)
{
  if (bytesPerSample == 1)
  {
    if (numChannels == 1)
    {
      return AL_FORMAT_MONO8;
    }
    else if (numChannels == 2)
    {
      return AL_FORMAT_STEREO8;
    }
  }
  else if (bytesPerSample == 2)
  {
    if (numChannels == 1)
    {
      return AL_FORMAT_MONO16;
    }
    else if (numChannels == 2)
    {
      return AL_FORMAT_STEREO16;
    }
  }

  return AL_NONE;
}

AudioDevice_OpenAL::AudioDevice_OpenAL()
{
  m_Device = alcOpenDevice(nullptr);

  const ALCint* attrList = nullptr;
  m_Context = alcCreateContext(m_Device, attrList);
  alcMakeContextCurrent(m_Context);
}

AudioDevice_OpenAL::~AudioDevice_OpenAL()
{
  alcCloseDevice(m_Device);

  alcMakeContextCurrent(nullptr);
  alcDestroyContext(m_Context);
}

AudioBuffer_OpenAL::AudioBuffer_OpenAL()
{
  alGenBuffers(1, &m_Buffer);
}

AudioBuffer_OpenAL::~AudioBuffer_OpenAL()
{
  alDeleteBuffers(1, &m_Buffer);
}

void AudioBuffer_OpenAL::Write(const uint8* bytes, uint32 size, const AudioData& info)
{
  const ALenum format = GetOpenALFormat(info.BytesPerSample, info.NumChannels);

  alBufferData(m_Buffer, format, bytes, size, info.SampleRate);
}

ALuint AudioBuffer_OpenAL::GetBuffer() const
{
  return m_Buffer;
}

AudioSource_OpenAL::AudioSource_OpenAL(AudioBuffer* buffer)
  : AudioSource(buffer)
{
  alGenSources(1, &m_Source);
}

AudioSource_OpenAL::~AudioSource_OpenAL()
{
  alDeleteSources(1, &m_Source);
}

void AudioSource_OpenAL::SetNonStreamingBuffer_Internal(AudioBuffer* buffer)
{
  AudioBuffer_OpenAL* al_buffer = static_cast<AudioBuffer_OpenAL*>(buffer);
  if (al_buffer)
  {
    alSourcei(m_Source, AL_BUFFER, al_buffer->GetBuffer());
  }
  else 
  {
    alSourcei(m_Source, AL_BUFFER, 0);
  }
}

void AudioSource_OpenAL::Play_Internal()
{
  alSourcePlay(m_Source);
}

void AudioSource_OpenAL::Stop_Internal()
{
  alSourceStop(m_Source);
}

void AudioSource_OpenAL::Pause_Internal()
{
  alSourcePause(m_Source);
}

void AudioSource_OpenAL::SetIsLooping_Internal(bool looping)
{
  alSourcei(m_Source, AL_LOOPING, looping);
}

void AudioSource_OpenAL::SetVolume_Internal(float volume)
{
  alSourcef(m_Source, AL_GAIN, volume);
}

AudioState AudioSource_OpenAL::GetState_Internal() const
{
  ALenum alState;
  alGetSourcei(m_Source, AL_SOURCE_STATE, &alState);
  switch (alState)
  {
  case AL_INITIAL:
  case AL_STOPPED: return AudioState::Stopped;
  case AL_PLAYING: return AudioState::Playing;
  case AL_PAUSED: return AudioState::Paused;
  }

  return AudioState::Stopped;
}

AudioBuffer* AudioBuffer::Create_OpenAL()
{
  return new AudioBuffer_OpenAL();
}

AudioDevice* AudioDevice::Create_OpenAL()
{
  return new AudioDevice_OpenAL();
}

AudioSource* AudioSource::Create_OpenAL(AudioBuffer* buffer)
{
  return new AudioSource_OpenAL(buffer);
}

ZK_NAMESPACE_END
