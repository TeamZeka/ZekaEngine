#ifndef _H_AUDIO_NONE
#define _H_AUDIO_NONE

#include "Audio.h"

ZK_NAMESPACE_BEGIN

class AudioDevice_None : public AudioDevice
{
public:
  AudioDevice_None() {}
  ~AudioDevice_None() {}
};

class AudioBuffer_None : public AudioBuffer
{
public:
  AudioBuffer_None() {}
  ~AudioBuffer_None() {}

  void Write(const uint8* bytes, uint32 size, const AudioData& info) override {}
};

class AudioSource_None : public AudioSource
{
public:
  AudioSource_None(AudioBuffer* buffer) : AudioSource(buffer) {}
  ~AudioSource_None() {}

  void SetNonStreamingBuffer_Internal(AudioBuffer* buffer) override {}
  void Play_Internal() override {}
  void Stop_Internal() override {}
  void Pause_Internal() override {}
  void SetIsLooping_Internal(bool looping) override {}
  void SetVolume_Internal(float volume) override {}
  AudioState GetState_Internal() const override { return AudioState::Stopped; }
};

ZK_NAMESPACE_END

#endif
