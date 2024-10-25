#ifndef _H_WINDOWS_ENGINE
#define _H_WINDOWS_ENGINE

#include "ZekaEngine/Engine.h"
#include "WindowsWindow.h"

ZK_NAMESPACE_BEGIN

class WindowsEngine : public Engine
{
public:
  WindowsEngine() {}
  ~WindowsEngine() {}

  void Terminate()
  {
    WindowsWindow* window = static_cast<WindowsWindow*>(m_Window);
    window->Terminate();
  }
};

ZK_NAMESPACE_END

#endif
