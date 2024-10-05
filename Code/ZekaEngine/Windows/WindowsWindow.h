#ifndef _H_WINDOWS_WINDOW
#define _H_WINDOWS_WINDOW

#include "ZekaEngine/Window.h"
#include "IncludeWindowsHeaders.h"

ZK_NAMESPACE_BEGIN

class WindowsWindow : public Window
{
public:
  WindowsWindow(const char* name, int width, int height, EventHandler& handler);
  ~WindowsWindow();

  LRESULT HandleMessages(UINT Msg, WPARAM wParam, LPARAM lParam);
  
  void PollEvents() override;
  void* GetHandle() const override;
  bool DestroyRequested() const override;
private:
  void Show();
private:
  HWND m_hWnd;
  bool m_DestroyRequested;
};

ZK_NAMESPACE_END

#endif
