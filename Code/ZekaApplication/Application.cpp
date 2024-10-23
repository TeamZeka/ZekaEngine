#include "ZekaEngine/Engine.h"
#include "ZekaEngine/Platform.h"
#include "ZekaEngine/Renderer.h"
#include "ZekaEngine/ImageTool.h"
#include "ZekaEngine/ShaderTool.h"
#include "ZekaEngine/Audio.h"
#include "ZekaEngine/FontManager.h"
#include "ZekaEngine/Font.h"
#include "ZekaEngine/FontTool.h"
#include "ZekaEngine/AudioDecoder.h"

#include <string>

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

  Zeka::Font* font;
  Zeka::Texture* texture;
  Zeka::AudioSource* source;
  Zeka::AudioBuffer* buffer;
  void OnInitialize() override
  {
    Application::OnInitialize();

    texture = Zeka::ImageTool::ImportTexture(Zeka::Engine::Get()->GetRenderDevice(), "resim.png");
    texture->SetWrapT(Zeka::TextureWrap::ClampToEdge);
    texture->SetWrapS(Zeka::TextureWrap::ClampToEdge);
    texture->SetMagFilter(Zeka::TextureFilter::Linear);
    texture->SetMinFilter(Zeka::TextureFilter::Linear);

    Zeka::Shader* vs = Zeka::ShaderTool::ImportShader(Zeka::Engine::Get()->GetRenderDevice(), "Draw2D_VS.glsl", Zeka::ShaderType::Vertex);
    Zeka::Shader* fs = Zeka::ShaderTool::ImportShader(Zeka::Engine::Get()->GetRenderDevice(), "Draw2D_Image_FS.glsl", Zeka::ShaderType::Fragment);
    Zeka::Shader* fs1 = Zeka::ShaderTool::ImportShader(Zeka::Engine::Get()->GetRenderDevice(), "Draw2D_Color_FS.glsl", Zeka::ShaderType::Fragment);
    Zeka::Shader* fs2 = Zeka::ShaderTool::ImportShader(Zeka::Engine::Get()->GetRenderDevice(), "Draw2D_Text_FS.glsl", Zeka::ShaderType::Fragment);
    Zeka::Shader* vs1 = Zeka::ShaderTool::ImportShader(Zeka::Engine::Get()->GetRenderDevice(), "Renderer_Line_VS.glsl", Zeka::ShaderType::Vertex);
    Zeka::Shader* fs3 = Zeka::ShaderTool::ImportShader(Zeka::Engine::Get()->GetRenderDevice(), "Renderer_Line_FS.glsl", Zeka::ShaderType::Fragment);
    Zeka::Shader* vs2 = Zeka::ShaderTool::ImportShader(Zeka::Engine::Get()->GetRenderDevice(), "Renderer_Quad_VS.glsl", Zeka::ShaderType::Vertex);
    Zeka::Shader* fs4 = Zeka::ShaderTool::ImportShader(Zeka::Engine::Get()->GetRenderDevice(), "Renderer_Quad_FS.glsl", Zeka::ShaderType::Fragment);

    renderer = new Zeka::Renderer({ Zeka::Engine::Get()->GetRenderDevice(), true, vs, fs, fs1, fs2, true, vs1, fs3, vs2, fs4 });
    renderer->SetDraw2DProjectionMatrix(Zeka::Matrix4::Orthographic(0.0f, (float)Zeka::Engine::Get()->GetWindow()->GetWidth(), (float)Zeka::Engine::Get()->GetWindow()->GetHeight(), 0.0f, -1.0f, 1.0f));
    renderer->SetProjectionViewMatrix(Zeka::Matrix4::Perspective(Zeka::Math::Radians(60.0f), 4.0f / 3.0f, 0.01f, 100.0f) * Zeka::Matrix4::Inverse(Zeka::Matrix4::Translate({ 0.0f, 0.0f, 10.0f })));

    device = Zeka::CreateAudioDevice();
    buffer = Zeka::CreateAudioBuffer();
    Zeka::WavDecoder decoder;
    Zeka::File* file = Zeka::OpenFile("test2.wav", Zeka::FileAccess::Read);
    
    Zeka::AudioData data;
    std::vector<Zeka::uint8> bytes;
    decoder.Read(file, bytes);
    data.BytesPerSample = decoder.GetBytesPerSample();
    data.NumChannels = decoder.GetNumChannels();
    data.NumSamples = decoder.GetNumSamples();
    data.SampleRate = decoder.GetSampleRate();

    buffer->Write(bytes.data(), bytes.size(), data);

    source = Zeka::CreateAudioSource();
    source->SetBuffer(buffer);
    source->SetVolume(1.0f);
    source->Play();
    
    Zeka::FontOptions options;
    options.Flags = Zeka::Font::AntiAliasing | Zeka::Font::Bold | Zeka::Font::Italic;
    options.Hinting = Zeka::FontHinting::Default;
    options.PointSize = 24.0f;
    font = Zeka::FontTool::ImportFont("geo_1.ttf", options);
  }

  void OnUpdate(float dt) override
  {
    Application::OnUpdate(dt);

    if (Zeka::Engine::Get()->GetWindow()->IsCreated())
    {
      Zeka::Engine::Get()->GetRenderDevice()->Clear(Zeka::ClearFlags::ClearColor | Zeka::ClearFlags::ClearDepth | Zeka::ClearFlags::ClearStencil);
      Zeka::Engine::Get()->GetRenderDevice()->ClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });

      renderer->DrawLine({ 3.0f, 0.0f, 1.0f }, { 4.0f, 4.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
      renderer->DrawTexture(Zeka::Matrix4::Translate({ 0.0f, 1.0f, 0.0f }), texture, {1.0f, 1.0f, 1.0f, 1.0f});
      renderer->Flush();

      draw2d.DrawTexture(Zeka::Vector2(), {100.0f, 100.0f}, texture, {1.0f});
      draw2d.DrawText(Zeka::Vector2(0.0f, 24.0f), font, "AVAV", {1.0f, 0.0f, 0.0f, 1.0f});
      renderer->FlushDraw2D(draw2d);
    }
  }

  void OnEvent(Zeka::Event& event) override
  {
    Application::OnEvent(event);

    Zeka::EventSorter sorter(event);
    sorter.SortEvent<Zeka::MouseButtonDownEvent>(ZK_GET_EVENT_FUNCTION(OnTouchDown));
  }

  void OnTouchDown(Zeka::MouseButtonDownEvent& event)
  {
    source->SetBuffer(buffer);
    source->Play();
  }

  Zeka::Renderer* renderer;
  Zeka::Draw2D draw2d;
  Zeka::Vector2 pos;
  Zeka::AudioDevice* device;
};

Zeka::Application* Zeka::CreateApplication()
{
  return new TestApplication();
}
