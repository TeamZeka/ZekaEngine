#ifndef _H_RENDERER
#define _H_RENDERER

#include "RHIBase.h"
#include "Matrix4.h"
#include "Draw2D.h"

ZK_NAMESPACE_BEGIN

struct RendererProps
{
  RenderDevice* Device;

  bool EnableDraw2D;
  Shader* Draw2D_VS;
  Shader* Draw2D_Image_FS;
  Shader* Draw2D_Color_FS;
  Shader* Draw2D_Text_FS;

  bool EnableRenderer2D;
  Shader* Renderer_Line_VS;
  Shader* Renderer_Line_FS;

  Shader* Renderer_Quad_VS;
  Shader* Renderer_Quad_FS;
};

class Renderer
{
public:
  Renderer(const RendererProps& props);
  ~Renderer();

  void SetDraw2DProjectionMatrix(const Matrix4& proj);
  void SetProjectionViewMatrix(const Matrix4& mat);
  void DrawLine(const Vector3& p0, const Vector3& p1, const Vector4& color);
  void DrawTexture(const Matrix4& transform, Texture* texture, const Vector4& color);
  void Flush();
  void FlushDraw2D(Draw2D& draw2d);
private:
  void InitializeDraw2DData();
  void InitializeLineRenderer();
  void CheckLineRendererBatch();
  void FlushLineRenderer();
  void InitializeQuadRenderer();
  void CheckQuadRendererBatch();
  void FlushQuadRenderer();
  float GetTextureIndex(Texture* texture);
private:
  RendererProps m_Props;
  RenderDevice* m_Device;
  Matrix4 m_ProjectionViewMatrix;
  Vector4 m_DefaultQuadPositions[4];
  Vector2 m_DefaultQuadUVs[4];

  struct
  {
    const uint32 MaxQuads = 20000;
    const uint32 MaxVertices = MaxQuads * 4;
    const uint32 MaxIndices = MaxQuads * 6;
    const uint32 MaxTextureSlots = 16;
  } m_Limits;

  struct
  {
    Matrix4 ProjectionMatrix;
    Buffer* VertexBuffer;
    Buffer* IndexBuffer;
    Buffer* UniformBuffer;
    Pipeline* ImagePipeline;
    Pipeline* ColorPipeline;
    Pipeline* TextPipeline;
  } m_Draw2DData;

  struct QuadVertex
  {
    Vector3 Position;
    Vector2 UV;
    Vector4 Color;
    float TextureIndex;
  };

  struct
  {
    Buffer* VertexBuffer;
    Buffer* IndexBuffer;
    Buffer* UniformBuffer;
    Pipeline* Pipeline;

    Texture* Textures[16];
    uint32 TextureIndex = 0;

    std::vector<QuadVertex> Vertices;
    uint32 IndexCount = 0;
  } m_QuadRenderer;

  struct LineVertex
  {
    Vector3 Position;
    Vector4 Color;
  };

  struct
  {
    Buffer* VertexBuffer;
    Buffer* UniformBuffer;
    Pipeline* Pipeline;

    std::vector<LineVertex> Vertices;
  } m_LineRenderer;
};

ZK_NAMESPACE_END

#endif
