#ifndef _H_IMAGE_TOOL
#define _H_IMAGE_TOOL

#include "RHIBase.h"

ZK_NAMESPACE_BEGIN

class ImageTool
{
public:
  static uint8* CreateFromMemory(const uint8* buffer, uint64 size, uint32& width, uint32& height, uint32& bits, bool flipY = false);
  static uint8* ImportImage(const char* filename, uint32& width, uint32& height, uint32& bits, bool flipY = false);
  static Texture* ImportTexture(RenderDevice* device, const char* filename, bool flipY = false);
};

ZK_NAMESPACE_END

#endif
