#include "Font.h"
#include "FontManager.h"
#include "Math.h"

#include <freetype/ftsynth.h>
#include <freetype/ftbitmap.h>

ZK_NAMESPACE_BEGIN

Font::Font(const uint8* data, uint32 size, const FontOptions& options)
  : m_Options(options)
{
  m_FontDPI = 96;

  FT_New_Memory_Face(FontManager::GetLibrary(), data, size, 0, &m_Face);
  FlushSize();

  m_HasKerning = FT_HAS_KERNING(m_Face) != 0;
  m_Height = Math::RoundToInt(FT_MulFix(m_Face->height, m_Face->size->metrics.y_scale) / 64.0f);
  m_Ascender = static_cast<int16>(Math::RoundToInt(m_Face->size->metrics.ascender / 64.0f));
  m_Descender = static_cast<int16>(Math::RoundToInt(m_Face->size->metrics.descender / 64.0f));
}

Font::~Font()
{
  if (m_Face)
  {
    FT_Done_Face(m_Face);
    m_Face = nullptr;
  }
}

float Font::GetPointSize() const
{
  return m_Options.PointSize;
}

int32 Font::GetHeight() const
{
  return m_Height;
}

int16 Font::GetAscender() const
{
  return m_Ascender;
}

int16 Font::GetDescender() const
{
  return m_Descender;
}

int16 Font::GetAdvanceX(char c) const
{
  return m_Characters.at(c).AdvanceX;
}

int Font::GetFontDPI() const
{
  return m_FontDPI;
}

bool Font::HasKerning() const
{
  return m_HasKerning;
}

bool Font::UseAntiAliasing() const
{
  return (m_Options.Flags & AntiAliasing) != 0;
}

bool Font::IsBold() const
{
  return (m_Options.Flags & Bold) != 0;
}

bool Font::IsItalic() const
{
  return (m_Options.Flags & Italic) != 0;
}

FontHinting Font::GetHinting() const
{
  return m_Options.Hinting;
}

int32 Font::GetKerning(int prev, int curr)
{
  if (m_HasKerning)
  {
    const uint32 key = (uint32)prev << 16 | curr;
    auto it = m_KerningTable.find(key);
    if (it == m_KerningTable.end())
    {
      FlushSize();

      FT_Vector vec;
      const FT_UInt firstIndex = FT_Get_Char_Index(m_Face, prev);
      const FT_UInt secondIndex = FT_Get_Char_Index(m_Face, curr);
      FT_Get_Kerning(m_Face, firstIndex, secondIndex, FT_KERNING_DEFAULT, &vec);
      
      int32 kerning = vec.x >> 6;
      m_KerningTable.insert({ key, kerning });

      return kerning;
    }

    return it->second;
  }

  return 0;
}

const FontCharacter& Font::GetCharacter(int c)
{
  auto it = m_Characters.find(c);
  if (it == m_Characters.end())
  {
    FontCharacter character;
    LoadChar(c, character);
    return character;
  }

  return it->second;
}

Texture* Font::GetAtlasTexture(uint32 index)
{
  return m_AtlasTextures[index];
}

bool Font::LoadChar(int c, FontCharacter& character)
{
  if (!m_Face)
  {
    return false;
  }

  FlushSize();

  const FT_Face face = m_Face;

  character.Character = c;

  uint32 loadFlags = FT_LOAD_NO_BITMAP;
  if (UseAntiAliasing())
  {
    switch (m_Options.Hinting)
    {
    case FontHinting::Auto: loadFlags |= FT_LOAD_FORCE_AUTOHINT; break;
    case FontHinting::AutoLight: loadFlags |= FT_LOAD_TARGET_LIGHT; break;
    case FontHinting::Monochrome: loadFlags |= FT_LOAD_TARGET_MONO; break;
    case FontHinting::None: loadFlags |= FT_LOAD_NO_AUTOHINT | FT_LOAD_NO_HINTING; break;
    case FontHinting::Default: loadFlags |= FT_LOAD_TARGET_NORMAL; break;
    }
  }
  else
  {
    loadFlags |= FT_LOAD_TARGET_MONO | FT_LOAD_FORCE_AUTOHINT;
  }

  const FT_UInt chrIdx = FT_Get_Char_Index(m_Face, c);
  FT_Load_Glyph(m_Face, chrIdx, loadFlags);
  if (IsBold())
  {
    FT_GlyphSlot_Embolden(m_Face->glyph);
  }
  if (IsItalic())
  {
    FT_GlyphSlot_Oblique(m_Face->glyph);
  }

  FT_GlyphSlot slot = face->glyph;
  FT_Render_Glyph(slot, UseAntiAliasing() ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO);
  character.AdvanceX = static_cast<int16>(Math::RoundToInt(slot->advance.x / 64.0f));
  character.OffsetX = slot->bitmap_left;
  character.OffsetY = -slot->bitmap_top;
  character.BearingY = static_cast<int16>(Math::RoundToInt(slot->metrics.horiBearingY / 64.0f));
  character.Width = slot->bitmap.width;
  character.Height = slot->bitmap.rows;

  uint32 texIndex = -1;
  if (character.Width > 0 && character.Height > 0)
  {
    FT_Bitmap* bitmap = &slot->bitmap;
    FT_Bitmap tmpBitmap;
    if (bitmap->pixel_mode != FT_PIXEL_MODE_GRAY)
    {
      FT_Bitmap_New(&tmpBitmap);
      FT_Bitmap_Convert(FontManager::GetLibrary(), bitmap, &tmpBitmap, 4);
      bitmap = &tmpBitmap;
    }

    const uint32 width = character.Width;
    const uint32 height = character.Height;

    uint8* imageData = new uint8[width * height];
    for (int32 row = 0; row < height; row++)
    {
      memcpy(&imageData[row * width], &bitmap->buffer[row * bitmap->pitch], width);
    }
    if (bitmap->num_grays != 256)
    {
      const int32 scale = 255 / (bitmap->num_grays - 1);
      for (uint32 i = 0; i < width * height; i++)
      {
        imageData[i] *= scale;
      }
    }

    if (bitmap == &tmpBitmap)
    {
      FT_Bitmap_Done(FontManager::GetLibrary(), bitmap);
      bitmap = nullptr;
    }

    texIndex = SetupTexture(width, height, imageData);
  }

  character.TextureIndex = texIndex;
  m_Characters.insert({ c, character });
  return true;
}

void Font::FlushSize() const
{
  FT_Set_Char_Size(m_Face, 0, static_cast<FT_F26Dot6>(Math::RoundToInt(m_Options.PointSize * 64.0f)), m_FontDPI, m_FontDPI);
}

uint32 Font::SetupTexture(uint32 width, uint32 height, const void* data)
{
  Texture* texture = FontManager::CreateTexture(width, height, data);

  const uint32 idx = m_AtlasTextures.size();
  m_AtlasTextures.push_back(texture);
  return idx;
}

float Font::CalculateStringWidth(const std::string& text)
{
  float result = 0.0f;

  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  std::wstring wtext = converter.from_bytes(text);

  int len = wtext.length();

  wchar_t prev = 0;
  int index = 0;
  while (index < len)
  {
    wchar_t c = wtext[index];
    if(index > 0) prev = wtext[index - 1];
    else prev = -1;
    FontCharacter character = GetCharacter(c);
    result += GetKerning(c, prev);
    result += character.AdvanceX;
    index++;
  }

  return result;
}

float Font::CalculateStringHeight(const std::string& text) const
{
  return m_Height;
}

ZK_NAMESPACE_END
