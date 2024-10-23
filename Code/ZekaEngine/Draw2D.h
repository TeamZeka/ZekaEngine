#ifndef _H_DRAW2D
#define _H_DRAW2D

#include "Vector4.h"
#include "Vector2.h"
#include "RHIBase.h"
#include "Font.h"

#include <vector>
#include <string>

ZK_NAMESPACE_BEGIN

enum class Draw2DPipelineType : uint32
{
  Image = 0,
  Color,
  Text
};

struct Draw2DVertex
{
  Vector2 Position;
  Vector2 UV;
  Vector4 Color;
};

struct Draw2DCommand
{
  uint32 Offset;
  uint32 Size;
  Texture* Texture;
  Draw2DPipelineType PipelineType;
};

class Draw2D
{
public:
  Draw2D();
  ~Draw2D();

  void DrawQuad(const Vector2& pos, const Vector2& size, const Vector4& color);
  void DrawTexture(const Vector2& pos, const Vector2& size, Texture* texture, const Vector4& color);
  void DrawText(const Vector2& pos, Font* font, const std::string& text, const Vector4& color);
  void Clear();

  const std::vector<Draw2DVertex>& GetVertices() const;
  const std::vector<uint32>& GetIndices() const;
  const std::vector<Draw2DCommand>& GetCommands() const;
private:
  std::vector<Draw2DVertex> m_Vertices;
  std::vector<uint32> m_Indices;
  std::vector<Draw2DCommand> m_Commands;
};

ZK_NAMESPACE_END

#endif
