#include "ZekaEngine/IncludeEngine.h"

using namespace Zeka;

class TestApplication : public Application
{
public:
  TestApplication()
  {
    GraphicsAPI::Set(GraphicsAPIType::OpenGL);

    m_Params.Name = "Test";
    m_Params.Width = 800;
    m_Params.Height = 600;
    m_Params.WindowResizable = true;
  }
  ~TestApplication() {}

  void OnInitialize() override
  {
    Application::OnInitialize();

    Engine::Get()->GetWindow()->GetGraphicsContext()->SetVSync(true);

    m_Texture = ImageTool::ImportTexture("resim.png");

    // AddToShaderQueue("Draw2D_VS.glsl", ShaderType::Vertex);
    // AddToShaderQueue("Draw2D_Image_FS.glsl", ShaderType::Fragment);
    // AddToShaderQueue("Draw2D_Color_FS.glsl", ShaderType::Fragment);
    // AddToShaderQueue("Draw2D_Text_FS.glsl", ShaderType::Fragment);
    // AddToShaderQueue("Renderer_Line_VS.glsl", ShaderType::Vertex);
    // AddToShaderQueue("Renderer_Line_FS.glsl", ShaderType::Fragment);
    // AddToShaderQueue("Renderer_Quad_VS.glsl", ShaderType::Vertex);
    // AddToShaderQueue("Renderer_Quad_FS.glsl", ShaderType::Fragment);
    // 
    // SaveShaderQueue();

    File* file = OpenFile("engine_shaders.pak", FileAccess::Read);
    Shader* vs = ShaderTool::ImportShader(file);
    Shader* fs = ShaderTool::ImportShader(file);
    Shader* fs1 = ShaderTool::ImportShader(file);
    Shader* fs2 = ShaderTool::ImportShader(file);
    Shader* vs1 = ShaderTool::ImportShader(file);
    Shader* fs3 = ShaderTool::ImportShader(file);
    Shader* vs2 = ShaderTool::ImportShader(file);
    Shader* fs4 = ShaderTool::ImportShader(file);

    const float width = (float)Engine::Get()->GetWindow()->GetWidth();
    const float height = (float)Engine::Get()->GetWindow()->GetHeight();

    m_Renderer = new Renderer({ Engine::Get()->GetRenderDevice(), true, vs, fs, fs1, fs2, true, vs1, fs3, vs2, fs4 });

    Engine::Get()->GetRenderDevice()->SetViewport(0, 0, width, height);
    m_Renderer->SetDraw2DProjectionMatrix(Matrix4::Orthographic(0.0f, width, height, 0.0f, -1.0f, 1.0f));
    m_Renderer->SetProjectionViewMatrix(Matrix4::Perspective(Math::Radians(60.0f), width / height, 0.01f, 100.0f) * Matrix4::Inverse(Matrix4::Translate({ 0.0f, 0.0f, 10.0f })));
    
    AudioDevice* device = AudioDevice::Create();
    AudioBuffer* buffer = AudioTool::ImportAudio("test1.wav");
    AudioSource* source = AudioSource::Create(buffer);
    source->Play();
  }

  void OnUpdate(float dt) override
  {
    Application::OnUpdate(dt);

    const float width = (float)Engine::Get()->GetWindow()->GetWidth();
    const float height = (float)Engine::Get()->GetWindow()->GetHeight();
    
    Engine::Get()->GetRenderDevice()->SetViewport(0, 0, width, height);
    m_Renderer->SetDraw2DProjectionMatrix(Matrix4::Orthographic(0.0f, width, height, 0.0f, -1.0f, 1.0f));
    m_Renderer->SetProjectionViewMatrix(Matrix4::Perspective(Math::Radians(60.0f), width / height, 0.01f, 100.0f) * Matrix4::Inverse(Matrix4::Translate({ 0.0f, 0.0f, 10.0f })));

    if (Engine::Get()->GetWindow()->IsCreated())
    {
      Engine::Get()->GetRenderDevice()->Clear(ClearFlags::ClearColor | ClearFlags::ClearDepth | ClearFlags::ClearStencil);
      Engine::Get()->GetRenderDevice()->ClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });

      m_Renderer->DrawLine({ 1.0f, 0.0f, 1.0f }, { 4.0f, 4.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
      m_Renderer->DrawTexture(Matrix4::Translate({ 0.0f, 1.0f, 0.0f }), m_Texture, {1.0f, 1.0f, 1.0f, 1.0f});
      m_Renderer->Flush();

      m_Draw2D.DrawTexture(Vector2(), { 100.0f, 100.0f }, { 0,0 }, { (float)m_Texture->GetWidth() * 0.5f, (float)m_Texture->GetHeight() * 0.5f }, m_Texture, {1.0f});
      m_Renderer->FlushDraw2D(m_Draw2D);
    }
  }

  void OnEvent(Event& event) override
  {
    Application::OnEvent(event);
  }

private:
  Renderer* m_Renderer;
  Texture* m_Texture;
  Draw2D m_Draw2D;

  struct ShaderSourceInfo
  {
    const char* Source;
    uint32 Size;

    ShaderType Type;
  };
  void AddToShaderQueue(const char* filename, ShaderType type)
  {
    File* file = OpenFile(filename, FileAccess::Read);

    uint32 size = file->GetSize();
    char* buffer = new char[size + 1];
    buffer[size] = 0;
    file->Read(buffer, size);
    file->Close();
    ShaderSourceInfo info;
    info.Source = (const char*)buffer;
    info.Size = size;
    info.Type = type;
    m_ShaderQueue.push_back(info);
  }

  void SaveShaderQueue()
  {
    File* stream = OpenFile("engine_shaders.pak", FileAccess::Write);
    for (const auto info : m_ShaderQueue)
    {
      ShaderTool::SaveShader(stream, info.Source, info.Size, info.Type);
    }
    m_ShaderQueue.clear();
    stream->Close();
  }
  std::vector<ShaderSourceInfo> m_ShaderQueue;
};

ZK_NAMESPACE_BEGIN
Application* CreateApplication()
{
  return new TestApplication();
}
ZK_NAMESPACE_END
