#include "Engine.h"
#include "Time.h"
#include "FontManager.h"
#include "Audio.h"

ZK_NAMESPACE_BEGIN

Engine* Engine::s_Engine = nullptr;

Engine::Engine()
{
  s_Engine = this;
}

Engine::~Engine()
{
  FontManager::Shutdown();
}

void Engine::SetApplication(Application* app)
{
  m_Application = app;
}

Application* Engine::GetApplication()
{
  return m_Application;
}

Window* Engine::GetWindow()
{
  return m_Window;
}

RenderDevice* Engine::GetRenderDevice()
{
  return m_RenderDevice;
}

void Engine::Run()
{
  m_EventHandler.Callback = ZK_GET_EVENT_FUNCTION(m_Application->OnEvent);

  Time::Initialize();

  const auto appCreateParams = m_Application->GetParams();
  m_Window = NewWindow(appCreateParams.Name, appCreateParams.Width, appCreateParams.Height, m_EventHandler);
  if (m_Window->IsCreated())
  {
    OnWindowCreated();
  }

  while (!m_Window->DestroyRequested())
  {
    m_Timer.Now = Time::Now();
    m_Timer.DeltaTime = float(m_Timer.Now - m_Timer.LastTime);
    m_Timer.LastTime = m_Timer.Now;

    m_Application->OnUpdate(m_Timer.DeltaTime);
    AudioSourceManager::Update();
    m_Window->PollEvents();
    m_Window->PresentGraphics();
  }
}

void Engine::OnWindowCreated()
{
  m_RenderDevice = CreateRenderDevice(m_Window->GetGraphicsContext());

  FontManager::Initialize(m_RenderDevice);

  m_Application->OnInitialize();
}

Engine* Engine::Get()
{
  return s_Engine;
}

ZK_NAMESPACE_END
