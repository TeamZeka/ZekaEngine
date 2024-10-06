#ifndef _H_WINDOW
#define _H_WINDOW

#include "GraphicsContext.h"
#include "Event.h"

ZK_NAMESPACE_BEGIN

class Window
{
public:
  Window(const char* name, int width, int height, EventHandler& handler);
  ~Window();

  virtual void PollEvents() {}
  virtual void* GetHandle() const { return nullptr; }
  virtual bool DestroyRequested() const { return false; }

  bool InitializeGraphics();
  void ShutdownGraphics();
  void PresentGraphics();
  GraphicsContext* GetGraphicsContext();

  int GetWidth() const;
  int GetHeight() const;
  const char* GetName() const;
  bool IsCreated() const;
protected:
  void OnWindowClosed();
  void OnWindowResized(int width, int height);
  void OnKeyDown(KeyCode code);
  void OnKeyUp(KeyCode code);
  void OnMouseButtonDown(MouseButton button);
  void OnMouseButtonUp(MouseButton button);
  void OnTouchDown(float x, float y, int32 pointerID);
  void OnTouchUp(float x, float y, int32 pointerID);
  void OnTouchMove(float x, float y, int32 pointerID);
protected:
  int m_Width;
  int m_Height;
  const char* m_Name;
  EventHandler& m_EventHandler;
  GraphicsContext* m_GraphicsContext;
  bool m_Created = false;
};

Window* NewWindow(const char* name, int width, int height, EventHandler& handler);

ZK_NAMESPACE_END

#endif
