#ifndef _H_FONT_MANAGER
#define _H_FONT_MANAGER

#include "IncludeFreeTypeHeaders.h"
#include "HelperDefines.h"
#include "RHIBase.h"

ZK_NAMESPACE_BEGIN

class FontManager
{
public:
  static void Initialize(RenderDevice* device);
  static void Shutdown();
  static FT_Library GetLibrary();
  static Texture* CreateTexture(uint32 width, uint32 height, const void* data);
private:
  static RenderDevice* s_RenderDevice;
};

ZK_NAMESPACE_END

#endif
