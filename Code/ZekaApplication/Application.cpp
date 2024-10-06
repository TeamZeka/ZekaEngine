#include "ZekaEngine/Engine.h"
#include "ZekaEngine/Platform.h"
#include "ZekaEngine/GraphicsAPI.h"

class TestApplication : public Zeka::Application
{
public:
  TestApplication()
  {
    Zeka::GraphicsAPI::Set(Zeka::GraphicsAPIType::OpenGL);

    m_Params.Name = "Test";
    m_Params.Width = 800;
    m_Params.Height = 600;
  }
  ~TestApplication() {}

  void OnInitialize() override
  {
    Application::OnInitialize();
      Zeka::PipelineDesc pdesc;
      pdesc.VertexShader = Zeka::Engine::Get()->GetRenderDevice()->CreateShader(R"(#version 300 es

  in vec2 pos;

  void main() { gl_Position = vec4(pos, 0.0, 1.0); }
  )", Zeka::ShaderType::Vertex);

      pdesc.FragmentShader = Zeka::Engine::Get()->GetRenderDevice()->CreateShader(R"(#version 300 es
precision mediump float;
out vec4 outColor;

  void main() { outColor = vec4(0.0, 1.0, 0.0, 1.0); }
  )", Zeka::ShaderType::Fragment);

      Zeka::VertexDecl decl;
      decl.PushElement(Zeka::RHIFormat::Float32Vector2);
      pdesc.VertexDecl = decl;
      pipeline = Zeka::Engine::Get()->GetRenderDevice()->CreatePipeline(pdesc);

      const float vertices[] = {
      -0.5f, -0.5f,
       0.5f, -0.5f,
       0.5f,  0.5f,
       -0.5f,  0.5f };

      vertex = Zeka::Engine::Get()->GetRenderDevice()->CreateBuffer(Zeka::BufferType::Vertex,
        vertices, 8 * sizeof(float), Zeka::BufferFlags::Static);

      const Zeka::uint32 indices[] = { 0, 1, 2, 2, 3, 0 };

      index = Zeka::Engine::Get()->GetRenderDevice()->CreateBuffer(Zeka::BufferType::Index,
        indices, 6 * sizeof(Zeka::uint32), Zeka::BufferFlags::Static);
  }
  void OnUpdate(float dt) override
  {
    Application::OnUpdate(dt);

    if (Zeka::Engine::Get()->GetWindow()->IsCreated())
    {
      Zeka::Engine::Get()->GetRenderDevice()->Clear(Zeka::ClearFlags::ClearColor);
      Zeka::Engine::Get()->GetRenderDevice()->ClearColor({1.0f, 0.0f, 0.0f, 1.0f});

      Zeka::Engine::Get()->GetRenderDevice()->SetPipeline(pipeline);

      Zeka::Engine::Get()->GetRenderDevice()->SetIndexBuffer(index);
      Zeka::Engine::Get()->GetRenderDevice()->SetVertexBuffer(vertex);

      Zeka::Engine::Get()->GetRenderDevice()->DrawIndexed(Zeka::PrimitiveType::TriangleList,Zeka::RHIFormat::UInt32, 0, 6);
    }
  }
  void OnEvent(Zeka::Event& event) override
  {
    Application::OnEvent(event);

    Zeka::EventSorter sorter(event);
    sorter.SortEvent<Zeka::KeyDownEvent>(ZK_GET_EVENT_FUNCTION(TestApplication::OnKeyDown));
  }

  void OnKeyDown(Zeka::KeyDownEvent& event)
  {
    if (event.Key == Zeka::KeyCode::A)
    {
    }
  }

  Zeka::Buffer* vertex;
  Zeka::Buffer* index;
  Zeka::Pipeline* pipeline;
};

Zeka::Application* Zeka::CreateApplication()
{
  return new TestApplication();
}
