#include "AndroidEngine.h"
#include "AndroidWindow.h"

ZK_NAMESPACE_BEGIN

Application* CreateApplication();

ZK_NAMESPACE_END

void HandleCmd(android_app* pApp, int32_t cmd)
{
  Zeka::AndroidEngine* engine = static_cast<Zeka::AndroidEngine*>(Zeka::Engine::Get());
  if (engine)
  {
    Zeka::AndroidWindow* window = static_cast<Zeka::AndroidWindow*>(engine->GetWindow());
    if (window)
    {
      window->HandleCmd(cmd);
    }
  }
}

int32_t HandleInput(android_app* app, AInputEvent* inputEvent)
{
  Zeka::AndroidEngine* engine = static_cast<Zeka::AndroidEngine*>(Zeka::Engine::Get());
  if (engine)
  {
    Zeka::AndroidWindow* window = static_cast<Zeka::AndroidWindow*>(engine->GetWindow());
    if (window)
    {
      return window->HandleInput(inputEvent);
    }
  }

  return 0;
}

void android_main(struct android_app* pApp)
{
  Zeka::Application* app = Zeka::CreateApplication();

  Zeka::AndroidEngine* engine = new Zeka::AndroidEngine();
  engine->SetApplication(app);
  engine->SetNativeApplication(pApp);

  pApp->onAppCmd = HandleCmd;
  pApp->onInputEvent = HandleInput;

  engine->Run();
}
