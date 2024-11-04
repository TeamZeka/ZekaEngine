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
public:
  static AudioDevice* Create_OpenAL();
  static AudioDevice* Create_None();
  static AudioDevice* Create();
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

  virtual void Write(const uint8* bytes, uint32 size, const AudioData& info) = 0;
public:
  static AudioBuffer* Create_OpenAL();
  static AudioBuffer* Create_None();
  static AudioBuffer* Create();
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
  AudioSource(AudioBuffer* buffer);
  ~AudioSource();

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
  virtual void SetNonStreamingBuffer_Internal(AudioBuffer* buffer) = 0;
  virtual void Play_Internal() = 0;
  virtual void Stop_Internal() = 0;
  virtual void Pause_Internal() = 0;
  virtual void SetIsLooping_Internal(bool looping) = 0;
  virtual void SetVolume_Internal(float volume) = 0;
  virtual AudioState GetState_Internal() const = 0;
private:
  AudioBuffer* m_Buffer;
  AudioState m_State;
  bool m_IsLooping;
  float m_Volume;
public:
  static AudioSource* Create_OpenAL(AudioBuffer* buffer);
  static AudioSource* Create_None(AudioBuffer* buffer);
  static AudioSource* Create(AudioBuffer* buffer);
};

inline 
AudioDevice* AudioDevice::Create()
{
  return AudioDevice::Create_OpenAL();
}

inline 
AudioBuffer* AudioBuffer::Create()
{
  return AudioBuffer::Create_OpenAL();
}

inline 
AudioSource* AudioSource::Create(AudioBuffer* buffer)
{
  return AudioSource::Create_OpenAL(buffer);
}

ZK_NAMESPACE_END

#endif
