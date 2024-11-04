#include "Window.h"

ZK_NAMESPACE_BEGIN

Window::Window(const char* name, int width, int height, bool resizable, EventHandler& handler)
  : m_Name(name)
  , m_Width(width)
  , m_Height(height)
  , m_EventHandler(handler)
{
  m_GraphicsContext = GraphicsContext::Create();
}

Window::~Window()
{
}

bool Window::InitializeGraphics()
{
  return m_GraphicsContext->InitializeGraphics(GetHandle());
}

void Window::ShutdownGraphics()
{
  m_GraphicsContext->ShutdownGraphics();
}

void Window::PresentGraphics()
{
  if (m_Created)
  {
    m_GraphicsContext->Present();
  }
}

GraphicsContext* Window::GetGraphicsContext()
{
  return m_GraphicsContext;
}

int Window::GetWidth() const
{
  return m_Width;
}

int Window::GetHeight() const
{
  return m_Height;
}

const char* Window::GetName() const
{
  return m_Name;
}

bool Window::IsCreated() const
{
  return m_Created;
}

bool Window::IsFullscreen() const
{
  return m_IsFullscreen;
}

void Window::OnWindowClosed()
{
  WindowCloseEvent event;

  m_EventHandler.CallEvent(event);
}

void Window::OnWindowResized(int width, int height)
{
  WindowSizeEvent event(width, height);

  m_EventHandler.CallEvent(event);
}

void Window::OnWindowMove(int x, int y)
{
  WindowMoveEvent event(x, y);

  m_EventHandler.CallEvent(event);
}

void Window::OnKeyDown(KeyCode code)
{
  KeyDownEvent event(code);

  m_EventHandler.CallEvent(event);
}

void Window::OnKeyUp(KeyCode code)
{
  KeyUpEvent event(code);

  m_EventHandler.CallEvent(event);
}

void Window::OnMouseButtonDown(MouseButton button)
{
  MouseButtonDownEvent event(button);

  m_EventHandler.CallEvent(event);
}

void Window::OnMouseButtonUp(MouseButton button)
{
  MouseButtonUpEvent event(button);

  m_EventHandler.CallEvent(event);
}

void Window::OnMouseMove(const Vector2& pos)
{
  MouseMoveEvent event(pos);

  m_EventHandler.CallEvent(event);
}

void Window::OnMouseWheel(const Vector2& axis)
{
  MouseWheelEvent event(axis);

  m_EventHandler.CallEvent(event);
}

void Window::OnTouchDown(const Vector2& pos, int32 pointerID)
{
  TouchDownEvent event(pos, pointerID);

  m_EventHandler.CallEvent(event);
}

void Window::OnTouchUp(const Vector2& pos, int32 pointerID)
{
  TouchUpEvent event(pos, pointerID);

  m_EventHandler.CallEvent(event);
}

void Window::OnTouchMove(const Vector2& pos, int32 pointerID)
{
  TouchMoveEvent event(pos, pointerID);

  m_EventHandler.CallEvent(event);
}

ZK_NAMESPACE_END
