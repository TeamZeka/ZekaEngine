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
  }
  ~TestApplication() {}

  void OnInitialize() override
  {
    Application::OnInitialize();

    m_Texture = ImageTool::ImportTexture("resim.png");

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

    m_Renderer->SetDraw2DProjectionMatrix(Matrix4::Orthographic(0.0f, width, height, 0.0f, -1.0f, 1.0f));
    m_Renderer->SetProjectionViewMatrix(Matrix4::Perspective(Math::Radians(60.0f), width / height, 0.01f, 100.0f) * Matrix4::Inverse(Matrix4::Translate({ 0.0f, 0.0f, 10.0f })));
    
    AudioDevice* device = CreateAudioDevice();
    AudioBuffer* buffer = AudioTool::ImportAudio("test2.wav");
    AudioSource* source = CreateAudioSource(buffer);
    source->Play();
  }

  void OnUpdate(float dt) override
  {
    Application::OnUpdate(dt);

    if (Engine::Get()->GetWindow()->IsCreated())
    {
      Engine::Get()->GetRenderDevice()->Clear(ClearFlags::ClearColor | ClearFlags::ClearDepth | ClearFlags::ClearStencil);
      Engine::Get()->GetRenderDevice()->ClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });

      m_Renderer->DrawLine({ 1.0f, 0.0f, 1.0f }, { 4.0f, 4.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
      m_Renderer->DrawTexture(Matrix4::Translate({ 0.0f, 1.0f, 0.0f }), m_Texture, {1.0f, 1.0f, 1.0f, 1.0f});
      m_Renderer->Flush();

      Draw2D draw2d;
      draw2d.DrawTexture(Vector2(), {100.0f, 100.0f}, m_Texture, {1.0f});
      m_Renderer->FlushDraw2D(draw2d);
    }
  }

  void OnEvent(Event& event) override
  {
    Application::OnEvent(event);
  }

private:
  Renderer* m_Renderer;
  Texture* m_Texture;

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
