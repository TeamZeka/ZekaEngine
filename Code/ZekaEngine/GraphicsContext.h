#ifndef _H_GRAPHICS_CONTEXT
#define _H_GRAPHICS_CONTEXT

#include "GraphicsAPI.h"

ZK_NAMESPACE_BEGIN

class GraphicsContext
{
public:
  GraphicsContext() : m_WindowHandle(nullptr) {}
  ~GraphicsContext() {}

  virtual bool InitializeGraphics(void* windowHandle) = 0;
  virtual void ShutdownGraphics() = 0;
  virtual void Present() = 0;
  virtual void SetVSync(bool vsync) = 0;

  void* GetWindowHandle() const { return m_WindowHandle; }
  bool IsVSync() const { return m_IsVSync; }
protected:
  void* m_WindowHandle;
  bool m_IsVSync;
public:
  static GraphicsContext* Create_OpenGL();
  static GraphicsContext* Create_None();
  static GraphicsContext* Create();
};

inline 
GraphicsContext* GraphicsContext::Create()
{
  switch (GraphicsAPI::Get())
  {
  case GraphicsAPIType::OpenGL: return GraphicsContext::Create_OpenGL();
  case GraphicsAPIType::None: return GraphicsContext::Create_None();
  }

  return nullptr;
}

ZK_NAMESPACE_END

#endif
