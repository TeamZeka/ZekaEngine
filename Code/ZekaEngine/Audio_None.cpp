#include "Audio_None.h"

ZK_NAMESPACE_BEGIN

AudioBuffer* AudioBuffer::Create_None()
{
  return new AudioBuffer_None();
}

AudioDevice* AudioDevice::Create_None()
{
  return new AudioDevice_None();
}

AudioSource* AudioSource::Create_None(AudioBuffer* buffer)
{
  return new AudioSource_None(buffer);
}

ZK_NAMESPACE_END
