#ifndef _H_AUDIO_TOOL
#define _H_AUDIO_TOOL

#include "AudioDecoder.h"

ZK_NAMESPACE_BEGIN

class AudioTool
{
public:
  static AudioBuffer* ImportAudio(const char* filename);
};

ZK_NAMESPACE_END

#endif
