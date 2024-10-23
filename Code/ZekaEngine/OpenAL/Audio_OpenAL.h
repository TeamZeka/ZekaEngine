#ifndef _H_AUDIO_OPENAL
#define _H_AUDIO_OPENAL

#include "ZekaEngine/Audio.h"

#include <AL/alc.h>
#include <AL/al.h>

ZK_NAMESPACE_BEGIN

class AudioDevice_OpenAL : public AudioDevice
{
public:
  AudioDevice_OpenAL();
  ~AudioDevice_OpenAL();
private:
  ALCdevice* m_Device;
  ALCcontext* m_Context;
};

class AudioBuffer_OpenAL : public AudioBuffer
{
public:
  AudioBuffer_OpenAL();
  ~AudioBuffer_OpenAL();

  void Write(const uint8* bytes, uint32 size, const AudioData& info) override;

  ALuint GetBuffer() const;
private:
  ALuint m_Buffer;
};

class AudioSource_OpenAL : public AudioSource
{
public:
  AudioSource_OpenAL();
  ~AudioSource_OpenAL();

  void SetBuffer_Internal(AudioBuffer* buffer) override;
  void Play_Internal() override;
  void Stop_Internal() override;
  void Pause_Internal() override;
  void SetIsLooping_Internal(bool looping) override;
  void SetVolume_Internal(float volume) override;
  AudioState GetState_Internal() const override;
private:
  ALuint m_Source;
};

ZK_NAMESPACE_END

#endif
