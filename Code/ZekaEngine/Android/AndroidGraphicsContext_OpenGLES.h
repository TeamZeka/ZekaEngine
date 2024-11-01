#ifndef _H_ANDROID_GRAPHICS_CONTEXT_OPENGLES
#define _H_ANDROID_GRAPHICS_CONTEXT_OPENGLES

#include "ZekaEngine/GraphicsContext.h"

#include <android_native_app_glue.h>

#include <EGL/egl.h>
#include <GLES3/gl3.h>

ZK_NAMESPACE_BEGIN

class AndroidGraphicsContext_OpenGLES : public GraphicsContext
{
public:
  AndroidGraphicsContext_OpenGLES();
  ~AndroidGraphicsContext_OpenGLES();

  bool InitializeGraphics(void* windowHandle) override;
  void ShutdownGraphics() override;
  void Present() override;
  void SetVSync(bool vsync) override;
private:
  EGLDisplay m_Display = EGL_NO_DISPLAY;
  EGLSurface m_Surface = EGL_NO_SURFACE;
  EGLContext m_Context = EGL_NO_CONTEXT;
};

ZK_NAMESPACE_END

#endif
