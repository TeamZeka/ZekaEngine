#include "FontManager.h"

#include <freetype/internal/ftdrv.h>

ZK_NAMESPACE_BEGIN

RenderDevice* FontManager::s_RenderDevice = nullptr;

static struct
{
  FT_Library Library;
} s_FontManagerData;

void FontManager::Initialize(RenderDevice* device)
{
  s_RenderDevice = device;

  FT_Init_FreeType(&s_FontManagerData.Library);
}

void FontManager::Shutdown()
{
  if (s_FontManagerData.Library)
  {
    FT_Done_Library(s_FontManagerData.Library);

    s_FontManagerData.Library = nullptr;
  }
}

FT_Library FontManager::GetLibrary()
{
  return s_FontManagerData.Library;
}

Texture* FontManager::CreateTexture(uint32 width, uint32 height, const void* data)
{
  Texture* texture = s_RenderDevice->CreateTexture(PixelFormat::r8UnsignedNorm, width, height, data);
  texture->SetWrapS(TextureWrap::Clamp);
  texture->SetWrapT(TextureWrap::Clamp);
  texture->SetMinFilter(TextureFilter::Linear);
  texture->SetMagFilter(TextureFilter::Linear);
  return texture;
}

ZK_NAMESPACE_END
