#ifndef _H_FONT
#define _H_FONT

#include "IncludeFreeTypeHeaders.h"
#include "Vector2.h"
#include "RHIBase.h"

#include <map>

ZK_NAMESPACE_BEGIN

struct FontCharacter
{
  char Character;
  int16 OffsetX;
  int16 OffsetY;
  int16 AdvanceX;
  int16 BearingY;
  uint32 Width;
  uint32 Height;
  uint32 TextureIndex;
};

enum class FontHinting : uint32
{
  Default = 0,
  Auto,
  AutoLight,
  Monochrome,
  None
};

struct FontOptions
{
  float PointSize;
  uint32 Flags;
  FontHinting Hinting;
};

class Font
{
public:
  enum : uint32
  {
    AntiAliasing = 1 << 0,
    Bold = 1 << 1,
    Italic = 1 << 2
  };

public:
  Font(const uint8* data, uint32 size, const FontOptions& options);
  ~Font();

  float GetPointSize() const;
  int32 GetHeight() const;
  int16 GetAscender() const;
  int16 GetDescender() const;
  int16 GetAdvanceX(char c) const;
  int GetFontDPI() const;
  bool HasKerning() const;
  bool UseAntiAliasing() const;
  bool IsBold() const;
  bool IsItalic() const;
  FontHinting GetHinting() const;
public:
  int32 GetKerning(char prev, char curr);
  const FontCharacter& GetCharacter(char c);
  Texture* GetAtlasTexture(uint32 index);
private:
  bool LoadChar(char c, FontCharacter& character);
  void FlushSize() const;
  uint32 SetupTexture(uint32 width, uint32 height, const void* data);
private:
  FT_Face m_Face;

  int32 m_Height;
  int16 m_Ascender;
  int16 m_Descender;
  int m_FontDPI;
  bool m_HasKerning;
  FontOptions m_Options;

  std::map<uint32, int32> m_KerningTable;
  std::map<char, FontCharacter> m_Characters;
  std::vector<Texture*> m_AtlasTextures;
};

ZK_NAMESPACE_END

#endif
