#include "Draw2D.h"
#include "Platform.h"

ZK_NAMESPACE_BEGIN

Draw2D::Draw2D()
{
}

Draw2D::~Draw2D()
{
}

void Draw2D::DrawQuad(const Vector2& pos, const Vector2& size, const Vector4& color)
{
  Draw2DCommand cmd;
  cmd.Offset = m_Indices.size();
  cmd.Size = 6;
  cmd.Texture = nullptr;
  cmd.PipelineType = Draw2DPipelineType::Color;
  m_Commands.push_back(cmd);
 
  const uint32 voff = m_Vertices.size();

  Draw2DVertex v0;
  v0.Position = Vector2(pos.X, pos.Y);
  v0.Color = color;
  m_Vertices.push_back(v0);

  Draw2DVertex v1;
  v1.Position = Vector2(pos.X + size.X, pos.Y);
  v1.Color = color;
  m_Vertices.push_back(v1);

  Draw2DVertex v2;
  v2.Position = Vector2(pos.X + size.X, pos.Y + size.Y);
  v2.Color = color;
  m_Vertices.push_back(v2);

  Draw2DVertex v3;
  v3.Position = Vector2(pos.X, pos.Y + size.Y);
  v3.Color = color;
  m_Vertices.push_back(v3);

  m_Indices.push_back(voff);
  m_Indices.push_back(voff + 1);
  m_Indices.push_back(voff + 2);
                      
  m_Indices.push_back(voff + 2);
  m_Indices.push_back(voff + 3);
  m_Indices.push_back(voff);
}

void Draw2D::DrawTexture(const Vector2& pos, const Vector2& size, Texture* texture, const Vector4& color)
{
  Draw2DCommand cmd;
  cmd.Offset = m_Indices.size();
  cmd.Size = 6;
  cmd.Texture = texture;
  cmd.PipelineType = Draw2DPipelineType::Image;
  m_Commands.push_back(cmd);

  const uint32 voff = m_Vertices.size();

  Draw2DVertex v0;
  v0.Position = Vector2(pos.X, pos.Y);
  v0.UV = Vector2(0.0f, 0.0f);
  v0.Color = color;
  m_Vertices.push_back(v0);

  Draw2DVertex v1;
  v1.Position = Vector2(pos.X + size.X, pos.Y);
  v1.UV = Vector2(1.0f, 0.0f);
  v1.Color = color;
  m_Vertices.push_back(v1);

  Draw2DVertex v2;
  v2.Position = Vector2(pos.X + size.X, pos.Y + size.Y);
  v2.UV = Vector2(1.0f, 1.0f);
  v2.Color = color;
  m_Vertices.push_back(v2);

  Draw2DVertex v3;
  v3.Position = Vector2(pos.X, pos.Y + size.Y);
  v3.UV = Vector2(0.0f, 1.0f);
  v3.Color = color;
  m_Vertices.push_back(v3);

  m_Indices.push_back(voff);
  m_Indices.push_back(voff + 1);
  m_Indices.push_back(voff + 2);
                      
  m_Indices.push_back(voff + 2);
  m_Indices.push_back(voff + 3);
  m_Indices.push_back(voff);
}

void Draw2D::DrawTexture(const Vector2& pos, const Vector2& size, const Vector2& spos, const Vector2& ssize, Texture* texture, const Vector4& color)
{
  Draw2DCommand cmd;
  cmd.Offset = m_Indices.size();
  cmd.Size = 6;
  cmd.Texture = texture;
  cmd.PipelineType = Draw2DPipelineType::Image;
  m_Commands.push_back(cmd);

  const uint32 voff = m_Vertices.size();
  const Vector2 textureSize = Vector2((float)texture->GetWidth(), (float)texture->GetHeight());

  Draw2DVertex v0;
  v0.Position = Vector2(pos.X, pos.Y);
  v0.UV = Vector2(spos.X, spos.Y) / textureSize;
  v0.Color = color;
  m_Vertices.push_back(v0);

  Draw2DVertex v1;
  v1.Position = Vector2(pos.X + size.X, pos.Y);
  v1.UV = Vector2(spos.X + ssize.X, spos.Y) / textureSize;
  v1.Color = color;
  m_Vertices.push_back(v1);

  Draw2DVertex v2;
  v2.Position = Vector2(pos.X + size.X, pos.Y + size.Y);
  v2.UV = Vector2(spos.X + ssize.X, spos.Y + ssize.Y) / textureSize;
  v2.Color = color;
  m_Vertices.push_back(v2);

  Draw2DVertex v3;
  v3.Position = Vector2(pos.X, pos.Y + size.Y);
  v3.UV = Vector2(spos.X, spos.Y + ssize.Y) / textureSize;
  v3.Color = color;
  m_Vertices.push_back(v3);

  m_Indices.push_back(voff);
  m_Indices.push_back(voff + 1);
  m_Indices.push_back(voff + 2);

  m_Indices.push_back(voff + 2);
  m_Indices.push_back(voff + 3);
  m_Indices.push_back(voff);
}

void Draw2D::DrawText(const Vector2& pos, Font* font, const std::string& text, const Vector4& color)
{
  Vector2 p = pos;
  char prev = 0;
  for (const auto c : text)
  {
    if (c == '\n')
    {
      p.X = pos.X;
      p.Y += static_cast<float>(font->GetHeight());
    }
    else
    {
      FontCharacter character = font->GetCharacter(c);
      if (!isspace(c))
      {
        if (prev != 0)
        {
          p.X += static_cast<float>(font->GetKerning(prev, c));
        }

        Draw2DCommand cmd;
        cmd.Offset = m_Indices.size();
        cmd.Size = 6;
        cmd.Texture = font->GetAtlasTexture(character.TextureIndex);
        cmd.PipelineType = Draw2DPipelineType::Text;
        m_Commands.push_back(cmd);

        const float x = static_cast<float>(character.OffsetX);
        const float y = static_cast<float>(character.OffsetY);
        const float width = static_cast<float>(character.Width);
        const float height = static_cast<float>(character.Height);

        const uint32 voff = m_Vertices.size();

        Draw2DVertex v0;
        v0.Position = p + Vector2(x, y);
        v0.UV = Vector2(0.0f, 0.0f);
        v0.Color = color;
        m_Vertices.push_back(v0);

        Draw2DVertex v1;
        v1.Position = p + Vector2(x + width, y);
        v1.UV = Vector2(1.0f, 0.0f);
        v1.Color = color;
        m_Vertices.push_back(v1);

        Draw2DVertex v2;
        v2.Position = p + Vector2(x + width, y + height);
        v2.UV = Vector2(1.0f, 1.0f);
        v2.Color = color;
        m_Vertices.push_back(v2);

        Draw2DVertex v3;
        v3.Position = p + Vector2(x, y + height);
        v3.UV = Vector2(0.0f, 1.0f);
        v3.Color = color;
        m_Vertices.push_back(v3);

        m_Indices.push_back(voff);
        m_Indices.push_back(voff + 1);
        m_Indices.push_back(voff + 2);

        m_Indices.push_back(voff + 2);
        m_Indices.push_back(voff + 3);
        m_Indices.push_back(voff);
      }

      p.X += static_cast<float>(character.AdvanceX);
    }

    prev = c;
  }
}

void Draw2D::Clear()
{
  m_Vertices.clear();
  m_Indices.clear();
  m_Commands.clear();
}

const std::vector<Draw2DVertex>& Draw2D::GetVertices() const
{
  return m_Vertices;
}

const std::vector<uint32>& Draw2D::GetIndices() const
{
  return m_Indices;
}

const std::vector<Draw2DCommand>& Draw2D::GetCommands() const
{
  return m_Commands;
}

ZK_NAMESPACE_END
