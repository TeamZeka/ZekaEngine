#include "Audio.h"
#include "Platform.h"

#include <string>

ZK_NAMESPACE_BEGIN

std::vector<AudioSource*> AudioSourceManager::s_Sources;

void AudioSourceManager::Add(AudioSource* source)
{
  s_Sources.push_back(source);
}

void AudioSourceManager::Remove(AudioSource* source)
{
  for (uint32 i = 0; i < s_Sources.size(); i++)
  {
    if (s_Sources[i] == source)
    {
      s_Sources.erase(s_Sources.begin() + i);
      break;
    }
  }
}

void AudioSourceManager::Update()
{
  for (AudioSource* source : s_Sources)
  {
    source->Update();
  }
}

AudioSource::AudioSource()
  : m_Buffer(nullptr)
  , m_State(AudioState::Stopped)
  , m_IsLooping(false)
  , m_Volume(1.0f)
{
  AudioSourceManager::Add(this);
}

AudioSource::~AudioSource() 
{
}

void AudioSource::SetBuffer(AudioBuffer* buffer)
{
  if (m_Buffer != buffer)
  {
    SetBuffer_Internal(buffer);

    m_Buffer = buffer;
  }
}

AudioBuffer* AudioSource::GetBuffer() const
{
  return m_Buffer;
}

void AudioSource::Play()
{
  if (m_State == AudioState::Playing || !m_Buffer)
  {
    return;
  }

  Play_Internal();
  m_State = AudioState::Playing;
}

void AudioSource::Stop()
{
  if (m_State != AudioState::Playing)
  {
    return;
  }

  Pause_Internal();
  m_State = AudioState::Paused;
}

void AudioSource::Pause()
{
  if (m_State == AudioState::Stopped)
  {
    return;
  }

  Stop_Internal();
  m_State = AudioState::Stopped;
}

AudioState AudioSource::GetState() const
{
  return m_State;
}

void AudioSource::SetIsLooping(bool looping)
{
  if (m_IsLooping != looping)
  {
    SetIsLooping_Internal(looping);

    m_IsLooping = looping;
  }
}

bool AudioSource::IsLooping() const
{
  return m_IsLooping;
}

void AudioSource::SetVolume(float volume)
{
  if (m_Volume != volume)
  {
    SetVolume_Internal(volume);

    m_Volume = volume;
  }
}

float AudioSource::GetVolume() const
{
  return m_Volume;
}

void AudioSource::Update()
{
  AudioState state = GetState_Internal();
  if (m_State != state)
  {
    m_State = state;
  }
}

ZK_NAMESPACE_END
