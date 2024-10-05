#include "WindowsEngine.h"
#include "WindowsWindow.h"

ZK_NAMESPACE_BEGIN

Application* CreateApplication();

ZK_NAMESPACE_END

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
  PSTR pCmdLine, int nCmdShow)
{
  Zeka::Application* app = Zeka::CreateApplication();

  Zeka::WindowsEngine* engine = new Zeka::WindowsEngine();
  engine->SetApplication(app);

  engine->Run();
  return 0;
}
