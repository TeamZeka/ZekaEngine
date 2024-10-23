#include "Renderer.h"

ZK_NAMESPACE_BEGIN

Renderer::Renderer(const RendererProps& props)
  : m_Props(props)
{
  m_Device = props.Device;

  m_DefaultQuadPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
  m_DefaultQuadPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
  m_DefaultQuadPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
  m_DefaultQuadPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

  m_DefaultQuadUVs[0] = { 0.0f, 1.0f };
  m_DefaultQuadUVs[1] = { 1.0f, 1.0f };
  m_DefaultQuadUVs[2] = { 1.0f, 0.0f };
  m_DefaultQuadUVs[3] = { 0.0f, 0.0f };

  if (props.EnableDraw2D)
  {
    InitializeDraw2DData();
  }

  if (props.EnableRenderer2D)
  {
    InitializeLineRenderer();
    InitializeQuadRenderer();
  }
}

Renderer::~Renderer()
{
}

void Renderer::SetDraw2DProjectionMatrix(const Matrix4& proj)
{
  m_Draw2DData.ProjectionMatrix = proj;
}

void Renderer::SetProjectionViewMatrix(const Matrix4& mat)
{
  m_ProjectionViewMatrix = mat;
}

void Renderer::DrawLine(const Vector3& p0, const Vector3& p1, const Vector4& color)
{
  CheckLineRendererBatch();

  LineVertex v0;
  v0.Position = p0;
  v0.Color = color;
  m_LineRenderer.Vertices.push_back(v0);

  LineVertex v1;
  v1.Position = p1;
  v1.Color = color;
  m_LineRenderer.Vertices.push_back(v1);
}

void Renderer::DrawTexture(const Matrix4& transform, Texture* texture, const Vector4& color)
{
  CheckQuadRendererBatch();

  float texIdx = GetTextureIndex(texture);
  for (uint32 i = 0; i < 4; i++)
  {
    QuadVertex vertex;
    vertex.Position = transform * m_DefaultQuadPositions[i];
    vertex.UV = m_DefaultQuadUVs[i];
    vertex.Color = color;
    vertex.TextureIndex = texIdx;
    m_QuadRenderer.Vertices.push_back(vertex);
  }

  m_QuadRenderer.IndexCount += 6;
}

void Renderer::Flush()
{
  if (m_Props.EnableRenderer2D)
  {
    FlushLineRenderer();
    FlushQuadRenderer();
  }
}

void Renderer::FlushDraw2D(Draw2D& draw2d)
{
  if (!m_Props.EnableDraw2D)
  {
    return;
  }

  const auto vertices = draw2d.GetVertices();
  const auto indices = draw2d.GetIndices();
  const auto cmds = draw2d.GetCommands();
  if (cmds.empty())
  {
    return;
  }

  m_Draw2DData.IndexBuffer->SetData(indices.data(), indices.size() * sizeof(uint32));
  m_Draw2DData.VertexBuffer->SetData(vertices.data(), vertices.size() * sizeof(Draw2DVertex));
  m_Draw2DData.UniformBuffer->SetData(&m_Draw2DData.ProjectionMatrix, sizeof(Matrix4));

  m_Device->SetIndexBuffer(m_Draw2DData.IndexBuffer);
  m_Device->SetVertexBuffer(m_Draw2DData.VertexBuffer);
  m_Device->SetUniformBuffer(m_Draw2DData.UniformBuffer, 0);

  for (const auto cmd : cmds)
  {
    if (cmd.Texture)
    {
      m_Device->SetTexture(cmd.Texture, 0);
    }

    if (cmd.PipelineType == Draw2DPipelineType::Color)
    {
      m_Device->SetPipeline(m_Draw2DData.ColorPipeline);
    }
    if (cmd.PipelineType == Draw2DPipelineType::Image)
    {
      m_Device->SetPipeline(m_Draw2DData.ImagePipeline);
    }
    if (cmd.PipelineType == Draw2DPipelineType::Text)
    {
      m_Device->SetPipeline(m_Draw2DData.TextPipeline);
    }

    m_Device->DrawIndexed(PrimitiveType::TriangleList, RHIFormat::UInt32, cmd.Offset * sizeof(uint32), cmd.Size);
  }

  draw2d.Clear();
}

void Renderer::InitializeDraw2DData()
{
  VertexDecl decl;
  decl.PushElement(RHIFormat::Float32Vector2);
  decl.PushElement(RHIFormat::Float32Vector2);
  decl.PushElement(RHIFormat::Float32Vector4);

  PipelineDesc desc;
  desc.VertexShader = m_Props.Draw2D_VS;
  desc.FragmentShader = m_Props.Draw2D_Image_FS;
  desc.VertexDecl = decl;
  desc.BlendingEnable = true;
  desc.BlendMode = BlendMode::SrcAlphaOneMinusSrcAlpha;
  desc.CullMode = CullMode::Normal;
  desc.DepthEnable = false;
  m_Draw2DData.ImagePipeline = m_Device->CreatePipeline(desc);

  desc.FragmentShader = m_Props.Draw2D_Color_FS;
  m_Draw2DData.ColorPipeline = m_Device->CreatePipeline(desc);

  desc.FragmentShader = m_Props.Draw2D_Text_FS;
  m_Draw2DData.TextPipeline = m_Device->CreatePipeline(desc);

  m_Draw2DData.VertexBuffer = m_Device->CreateBuffer(BufferType::Vertex, nullptr, 0, BufferFlags::Dynamic);
  m_Draw2DData.IndexBuffer = m_Device->CreateBuffer(BufferType::Index, nullptr, 0, BufferFlags::Dynamic);
  m_Draw2DData.UniformBuffer = m_Device->CreateBuffer(BufferType::Uniform, nullptr, sizeof(Matrix4), BufferFlags::Dynamic);
}

void Renderer::InitializeLineRenderer()
{
  VertexDecl decl;
  decl.PushElement(RHIFormat::Float32Vector3);
  decl.PushElement(RHIFormat::Float32Vector4);

  PipelineDesc desc;
  desc.VertexShader = m_Props.Renderer_Line_VS;
  desc.FragmentShader = m_Props.Renderer_Line_FS;
  desc.VertexDecl = decl;
  desc.BlendingEnable = true;
  desc.BlendMode = BlendMode::SrcAlphaOneMinusSrcAlpha;
  desc.CullMode = CullMode::Normal;
  desc.DepthEnable = true;
  desc.DepthFunc = ComparisonFunc::Always;
  m_LineRenderer.Pipeline = m_Device->CreatePipeline(desc);
  
  m_LineRenderer.VertexBuffer = m_Device->CreateBuffer(BufferType::Vertex, nullptr, m_Limits.MaxVertices * sizeof(LineVertex), BufferFlags::Dynamic);
  m_LineRenderer.UniformBuffer = m_Device->CreateBuffer(BufferType::Uniform, nullptr, sizeof(Matrix4), BufferFlags::Dynamic);
}

void Renderer::CheckLineRendererBatch()
{
  if (m_LineRenderer.Vertices.size() >= m_Limits.MaxVertices)
  {
    FlushLineRenderer();
  }
}

void Renderer::FlushLineRenderer()
{
  if (!m_LineRenderer.Vertices.empty())
  {
    m_LineRenderer.VertexBuffer->SetData(m_LineRenderer.Vertices.data(), m_LineRenderer.Vertices.size() * sizeof(LineVertex));
    m_LineRenderer.UniformBuffer->SetData(&m_ProjectionViewMatrix, sizeof(Matrix4));

    m_Device->SetVertexBuffer(m_LineRenderer.VertexBuffer);
    m_Device->SetUniformBuffer(m_LineRenderer.UniformBuffer, 0);

    m_Device->SetPipeline(m_LineRenderer.Pipeline);

    m_Device->DrawArrays(PrimitiveType::LineList, 0, m_LineRenderer.Vertices.size());

    m_LineRenderer.Vertices.clear();
  }
}

void Renderer::InitializeQuadRenderer()
{
  VertexDecl decl;
  decl.PushElement(RHIFormat::Float32Vector3);
  decl.PushElement(RHIFormat::Float32Vector2);
  decl.PushElement(RHIFormat::Float32Vector4);
  decl.PushElement(RHIFormat::Float32);

  PipelineDesc desc;
  desc.VertexShader = m_Props.Renderer_Quad_VS;
  desc.FragmentShader = m_Props.Renderer_Quad_FS;
  desc.VertexDecl = decl;
  desc.BlendingEnable = true;
  desc.BlendMode = BlendMode::SrcAlphaOneMinusSrcAlpha;
  desc.CullMode = CullMode::Back;
  desc.DepthEnable = true;
  desc.DepthFunc = ComparisonFunc::Always;
  m_QuadRenderer.Pipeline = m_Device->CreatePipeline(desc);

  m_QuadRenderer.VertexBuffer = m_Device->CreateBuffer(BufferType::Vertex, nullptr, m_Limits.MaxVertices * sizeof(QuadVertex), BufferFlags::Dynamic);

  uint32* indices = new uint32[m_Limits.MaxIndices];
  for (uint32 i = 0; i < m_Limits.MaxQuads; i++)
  {
    indices[i * 6] = i * 4;
    indices[i * 6 + 1] = i * 4 + 1;
    indices[i * 6 + 2] = i * 4 + 2;

    indices[i * 6 + 3] = i * 4 + 2;
    indices[i * 6 + 4] = i * 4 + 3;
    indices[i * 6 + 5] = i * 4;
  }

  m_QuadRenderer.IndexBuffer = m_Device->CreateBuffer(BufferType::Index, indices, m_Limits.MaxIndices * sizeof(uint32), BufferFlags::Static);
  m_QuadRenderer.UniformBuffer = m_Device->CreateBuffer(BufferType::Uniform, nullptr, sizeof(Matrix4), BufferFlags::Dynamic);
}

void Renderer::CheckQuadRendererBatch()
{
  if (m_QuadRenderer.IndexCount >= m_Limits.MaxIndices || m_QuadRenderer.TextureIndex >= m_Limits.MaxTextureSlots)
  {
    FlushQuadRenderer();
  }
}

void Renderer::FlushQuadRenderer()
{
  if (m_QuadRenderer.IndexCount > 0)
  {
    m_QuadRenderer.VertexBuffer->SetData(m_QuadRenderer.Vertices.data(), m_QuadRenderer.Vertices.size() * sizeof(QuadVertex));
    m_QuadRenderer.UniformBuffer->SetData(&m_ProjectionViewMatrix, sizeof(Matrix4));

    m_Device->SetIndexBuffer(m_QuadRenderer.IndexBuffer);
    m_Device->SetVertexBuffer(m_QuadRenderer.VertexBuffer);
    m_Device->SetUniformBuffer(m_QuadRenderer.UniformBuffer, 0);

    m_Device->SetPipeline(m_QuadRenderer.Pipeline);
    for (uint32 i = 0; i < m_QuadRenderer.TextureIndex; i++)
    {
      m_Device->SetTexture(m_QuadRenderer.Textures[i], i);
    }

    m_Device->DrawIndexed(PrimitiveType::TriangleList, RHIFormat::UInt32, 0, m_QuadRenderer.IndexCount);

    m_QuadRenderer.Vertices.clear();
    m_QuadRenderer.IndexCount = 0;
    m_QuadRenderer.TextureIndex = 0;
  }
}

float Renderer::GetTextureIndex(Texture* texture)
{
  float idx = -1.0f;
  for (uint32 i = 0; i < m_QuadRenderer.TextureIndex; i++)
  {
    if (m_QuadRenderer.Textures[i] == texture)
    {
      idx = (float)i;
      break;
    }
  }

  if (idx < 0.0f)
  {
    m_QuadRenderer.Textures[m_QuadRenderer.TextureIndex] = texture;
    idx = (float)m_QuadRenderer.TextureIndex;
    m_QuadRenderer.TextureIndex++;
  }

  return idx;
}

ZK_NAMESPACE_END
