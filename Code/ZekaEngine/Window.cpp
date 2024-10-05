#include "Window.h"

ZK_NAMESPACE_BEGIN

Window::Window(const char* name, int width, int height, EventHandler& handler)
  : m_Name(name)
  , m_Width(width)
  , m_Height(height)
  , m_EventHandler(handler)
{
  m_GraphicsContext = CreateGraphicsContext();
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
  m_GraphicsContext->Present();
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

void Window::OnTouchDown(float x, float y, int32 pointerID)
{
  TouchDownEvent event(x, y, pointerID);

  m_EventHandler.CallEvent(event);
}

void Window::OnTouchUp(float x, float y, int32 pointerID)
{
  TouchUpEvent event(x, y, pointerID);

  m_EventHandler.CallEvent(event);
}

void Window::OnTouchMove(float x, float y, int32 pointerID)
{
  TouchMoveEvent event(x, y, pointerID);

  m_EventHandler.CallEvent(event);
}

ZK_NAMESPACE_END
