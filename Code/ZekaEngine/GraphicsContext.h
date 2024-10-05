#ifndef _H_GRAPHICS_CONTEXT
#define _H_GRAPHICS_CONTEXT

#include "GraphicsAPI.h"

ZK_NAMESPACE_BEGIN

class GraphicsContext
{
public:
  GraphicsContext() : m_WindowHandle(nullptr) {}
  ~GraphicsContext() {}

  virtual bool InitializeGraphics(void* windowHandle) { return false; }
  virtual void ShutdownGraphics() {}
  virtual void Present() {}

  void* GetWindowHandle() const { return m_WindowHandle; }
protected:
  void* m_WindowHandle;
};

GraphicsContext* CreateGraphicsContext_OpenGL();
GraphicsContext* CreateGraphicsContext_None();

inline 
GraphicsContext* CreateGraphicsContext()
{
  switch (GraphicsAPI::Get())
  {
  case GraphicsAPIType::OpenGL: return CreateGraphicsContext_OpenGL();
  case GraphicsAPIType::None: return CreateGraphicsContext_None();
  }

  return nullptr;
}

ZK_NAMESPACE_END

#endif
