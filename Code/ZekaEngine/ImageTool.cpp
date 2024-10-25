#include "ImageTool.h"
#include "FileSystem.h"
#include "Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <memory.h>

ZK_NAMESPACE_BEGIN

uint8* ImageTool::CreateFromMemory(const uint8* buffer, uint64 size, uint32& width, uint32& height, uint32& bits, bool flipY)
{
  stbi_set_flip_vertically_on_load(flipY ? 1 : 0);

  int texWidth = 0, texHeight = 0, texChannels = 0;
  stbi_uc* pixels = nullptr;
  int sizeOfChannel = 8;
  pixels = stbi_load_from_memory(buffer, size, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

  if (!pixels)
  {
    texChannels = 4;

    width = 2;
    height = 2;
    bits = texChannels * sizeOfChannel;

    const int32 size = width * height * texChannels;
    uint8* data = new uint8[size];

    uint8 datatwo[16] = {
        255, 0, 255, 255,
        0, 0, 0, 255,
        0, 0, 0, 255,
        255, 0, 255, 255
    };

    memcpy(data, datatwo, size);
    return data;
  }

  if (texChannels != 4)
  {
    texChannels = 4;
  }

  width = texWidth;
  height = texHeight;
  bits = texChannels * sizeOfChannel; // texChannels;	  //32 bits for 4 bytes r g b a

  const uint64 sz = uint64(texWidth) * uint64(texHeight) * uint64(texChannels) * uint64(sizeOfChannel / 8U);
  uint8* result = new uint8[sz];
  memcpy(result, pixels, sz);

  stbi_image_free(pixels);
  return result;
}

uint8* ImageTool::ImportImage(const char* filename, uint32& width, uint32& height, uint32& bits, bool flipY)
{
  File* file = OpenFile(filename, FileAccess::Read);
  uint64 size = file->GetSize();

  uint8* buffer = new uint8[size];
  file->Read(buffer, size);
  file->Close();

  return CreateFromMemory(buffer, size, width, height, bits, flipY);
}

static PixelFormat BitsToFormat(uint32 bits)
{
  switch (bits)
  {
  case 8: return PixelFormat::r8UnsignedNorm;
  case 16: return PixelFormat::rg8UnsignedNorm;
  case 32: return PixelFormat::rgba8UnsignedNorm;
  case 64: return PixelFormat::rgba16Float;
  case 128: return PixelFormat::rgba32Float;
  }
}

Texture* ImageTool::ImportTexture(const char* filename, bool flipY)
{
  uint32 width = 0;
  uint32 height = 0;
  uint32 bits = 0;
  uint8* data = ImportImage(filename, width, height, bits, flipY);

  PixelFormat format = BitsToFormat(bits);

  Texture* texture = Engine::Get()->GetRenderDevice()->CreateTexture(format, width, height, data);
  texture->SetWrapT(TextureWrap::Repeat);
  texture->SetWrapS(TextureWrap::Repeat);
  texture->SetMagFilter(TextureFilter::Linear);
  texture->SetMinFilter(TextureFilter::Linear);
  return texture;
}

ZK_NAMESPACE_END
