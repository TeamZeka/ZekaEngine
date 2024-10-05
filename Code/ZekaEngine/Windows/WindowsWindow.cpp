#include "WindowsWindow.h"

ZK_NAMESPACE_BEGIN

static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) 
{
  WindowsWindow* pWindow = reinterpret_cast<WindowsWindow*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
  if (pWindow)
  {
    return pWindow->HandleMessages(Msg, wParam, lParam);
  }

  return DefWindowProcW(hWnd, Msg, wParam, lParam);
}

WindowsWindow::WindowsWindow(const char* name, int width, int height, EventHandler& handler)
  : Window(name, width, height, handler)
{
  m_DestroyRequested = false;

  HINSTANCE hInstance = GetModuleHandleW(nullptr);
  const WCHAR* wndClassName = L"Zeka Window";

  WNDCLASSEXW wndclass = {};
  wndclass.cbSize = sizeof(WNDCLASSEXW);
  wndclass.style = CS_HREDRAW | CS_VREDRAW;
  wndclass.hInstance = hInstance;
  wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(101));
  wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wndclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
  wndclass.lpszClassName = wndClassName;
  wndclass.lpfnWndProc = WndProc;
  RegisterClassExW(&wndclass);

  DWORD dwStyle = 0, dwExStyle = 0;
  dwExStyle |= WS_EX_APPWINDOW;
  dwStyle |= WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX | WS_THICKFRAME;

  RECT rect = { 0, 0, (LONG)width, (LONG)height };
  AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);

  const int w = rect.right - rect.left;
  const int h = rect.bottom - rect.top;

  WCHAR* wbuf = CreateWideString(name);
  m_hWnd = CreateWindowExW(dwExStyle,
    wndClassName,
    wbuf, dwStyle,
    CW_USEDEFAULT, CW_USEDEFAULT, w, h,
    nullptr, nullptr, hInstance, nullptr);

  delete[] wbuf;

  SetWindowLongPtrW(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

  Show();
}

WindowsWindow::~WindowsWindow()
{
  if (m_hWnd)
  {
    DestroyWindow(m_hWnd);
    m_hWnd = NULL;
  }
}

LRESULT WindowsWindow::HandleMessages(UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
  case WM_CLOSE:
  {
    OnWindowClosed();

    m_DestroyRequested = true;
    PostQuitMessage(0);
  } break;
  case WM_SIZE:
  {
    const int width = int(LOWORD(lParam)); 
    const int height = int(HIWORD(lParam));

    m_Width = width;
    m_Height = height;

    OnWindowResized(width, height);
  } break;
  case WM_KEYDOWN:
  {
    OnKeyDown(KeyCode((int)wParam));
  } break;
  case WM_KEYUP:
  {
    OnKeyUp(KeyCode((int)wParam));
  } break;
  case WM_LBUTTONDOWN: 
  {
    OnMouseButtonDown(MouseButton::Left);
  } break;
  case WM_RBUTTONDOWN: 
  {
    OnMouseButtonDown(MouseButton::Right);
  } break;
  case WM_MBUTTONDOWN: 
  {
    OnMouseButtonDown(MouseButton::Middle);
  } break;
  case WM_XBUTTONDOWN: 
  {
    if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) 
    {
      OnMouseButtonDown(MouseButton::XButton1);
    }
    if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2) 
    {
      OnMouseButtonDown(MouseButton::XButton2);
    }
  } break;
  case WM_LBUTTONUP: 
  {
    OnMouseButtonUp(MouseButton::Left);
  } break;
  case WM_RBUTTONUP: 
  {
    OnMouseButtonUp(MouseButton::Right);
  } break;
  case WM_MBUTTONUP: 
  {
    OnMouseButtonUp(MouseButton::Middle);
  } break;
  case WM_XBUTTONUP: 
  {
    if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) 
    {
      OnMouseButtonUp(MouseButton::XButton1);
    }
    if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2) 
    {
      OnMouseButtonUp(MouseButton::XButton2);
    }
  } break;
  }

  return DefWindowProcW(m_hWnd, Msg, wParam, lParam);
}

void WindowsWindow::PollEvents()
{
  MSG Msg;
  while (PeekMessageW(&Msg, NULL, 0, 0, PM_REMOVE) > 0)
  {
    TranslateMessage(&Msg);
    DispatchMessageW(&Msg);
  }
}

void* WindowsWindow::GetHandle() const
{
  return (void*)m_hWnd;
}

bool WindowsWindow::DestroyRequested() const
{
  return m_DestroyRequested;
}

void WindowsWindow::Show()
{
  InitializeGraphics();

  ShowWindow(m_hWnd, SW_SHOW);
  SetFocus(m_hWnd);
}

Window* NewWindow(const char* name, int width, int height, EventHandler& handler)
{
  return new WindowsWindow(name, width, height, handler);
}

ZK_NAMESPACE_END
