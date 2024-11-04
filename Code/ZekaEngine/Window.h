#ifndef _H_WINDOW
#define _H_WINDOW

#include "GraphicsContext.h"
#include "Event.h"

ZK_NAMESPACE_BEGIN

class Window
{
public:
  Window(const char* name, int width, int height, bool resizable, EventHandler& handler);
  ~Window();

  virtual void PollEvents() = 0;
  virtual void* GetHandle() const = 0;
  virtual bool DestroyRequested() const = 0;
  virtual void SetFullscreen(bool fullscreen) = 0;

  bool InitializeGraphics();
  void ShutdownGraphics();
  void PresentGraphics();
  GraphicsContext* GetGraphicsContext();

  int GetWidth() const;
  int GetHeight() const;
  const char* GetName() const;
  bool IsCreated() const;
  bool IsFullscreen() const;
protected:
  void OnWindowClosed();
  void OnWindowResized(int width, int height);
  void OnWindowMove(int x, int y);
  void OnKeyDown(KeyCode code);
  void OnKeyUp(KeyCode code);
  void OnMouseButtonDown(MouseButton button);
  void OnMouseButtonUp(MouseButton button);
  void OnMouseMove(const Vector2& pos);
  void OnMouseWheel(const Vector2& axis);
  void OnTouchDown(const Vector2& pos, int32 pointerID);
  void OnTouchUp(const Vector2& pos, int32 pointerID);
  void OnTouchMove(const Vector2& pos, int32 pointerID);
protected:
  int m_Width;
  int m_Height;
  const char* m_Name;
  EventHandler& m_EventHandler;
  GraphicsContext* m_GraphicsContext;
  bool m_Created = false;
  bool m_IsFullscreen = false;
public:
  static Window* Create(const char* name, int width, int height, bool resizable, EventHandler& handler);
};

ZK_NAMESPACE_END

#endif
