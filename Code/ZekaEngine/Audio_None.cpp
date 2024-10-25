#include "Audio_None.h"

ZK_NAMESPACE_BEGIN

AudioBuffer* CreateAudioBuffer_None()
{
  return new AudioBuffer_None();
}

AudioDevice* CreateAudioDevice_None()
{
  return new AudioDevice_None();
}

AudioSource* CreateAudioSource_None(AudioBuffer* buffer)
{
  return new AudioSource_None(buffer);
}

ZK_NAMESPACE_END
