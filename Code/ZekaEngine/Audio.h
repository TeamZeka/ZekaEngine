#ifndef _H_AUDIO
#define _H_AUDIO

#include "Vector3.h"

#include <vector>

ZK_NAMESPACE_BEGIN

class AudioDevice
{
public:
  AudioDevice() {}
  ~AudioDevice() {}
};

struct AudioData
{
  uint32 BytesPerSample;
  uint32 NumChannels;
  uint32 SampleRate;
  uint32 NumSamples;
};

class AudioBuffer
{
public:
  AudioBuffer() {}
  ~AudioBuffer() {}

  virtual void Write(const uint8* bytes, uint32 size, const AudioData& info) {}
};

class AudioSource;

class AudioSourceManager
{
public:
  static void Add(AudioSource* source);
  static void Remove(AudioSource* source);
  static void Update();
private:
  static std::vector<AudioSource*> s_Sources;
};

enum class AudioState : uint32
{
  Playing = 0,
  Stopped,
  Paused
};

class AudioSource
{
public:
  AudioSource();
  ~AudioSource();

  void SetBuffer(AudioBuffer* buffer);
  AudioBuffer* GetBuffer() const;
  void Play();
  void Stop();
  void Pause();
  AudioState GetState() const;
  void SetIsLooping(bool looping);
  bool IsLooping() const;
  void SetVolume(float volume);
  float GetVolume() const;
  void Update();
private:
  virtual void SetBuffer_Internal(AudioBuffer* buffer) {}
  virtual void Play_Internal() {}
  virtual void Stop_Internal() {}
  virtual void Pause_Internal() {}
  virtual void SetIsLooping_Internal(bool looping) {}
  virtual void SetVolume_Internal(float volume) {}
  virtual AudioState GetState_Internal() const { return AudioState::Stopped; }
private:
  AudioBuffer* m_Buffer;
  AudioState m_State;
  bool m_IsLooping;
  float m_Volume;
};

AudioDevice* CreateAudioDevice();
AudioBuffer* CreateAudioBuffer();
AudioSource* CreateAudioSource();

ZK_NAMESPACE_END

#endif
