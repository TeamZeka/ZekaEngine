#include "AndroidGraphicsContext_OpenGLES.h"

#include <memory>
#include <vector>

ZK_NAMESPACE_BEGIN

AndroidGraphicsContext_OpenGLES::AndroidGraphicsContext_OpenGLES()
{
}

AndroidGraphicsContext_OpenGLES::~AndroidGraphicsContext_OpenGLES()
{
}

bool AndroidGraphicsContext_OpenGLES::InitializeGraphics(void* windowHandle)
{
  m_WindowHandle = windowHandle;

  m_Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (m_Display == EGL_NO_DISPLAY)
  {
    return false;
  }

  if (!eglInitialize(m_Display, NULL/*major*/, NULL/*minor*/))
  {
    return false;
  }

  EGLint numConfigs;

  EGLint configAttribs[] =
  {
    EGL_DEPTH_SIZE,      16,
    EGL_RED_SIZE,        8,
    EGL_GREEN_SIZE,      8,
    EGL_BLUE_SIZE,       8,
    EGL_ALPHA_SIZE,      8,
    EGL_STENCIL_SIZE,    8,
    EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    EGL_NONE
  };

  EGLConfig config;
  eglChooseConfig(m_Display, configAttribs, &config, 1, &numConfigs);

  if (numConfigs < 1)
  {
    return false;
  }

  EGLint surfaceAttrs[] =
  {
    EGL_RENDER_BUFFER,
    EGL_BACK_BUFFER,
    EGL_NONE
  };

  m_Surface = eglCreateWindowSurface(m_Display, config, (ANativeWindow*)windowHandle, surfaceAttrs);
  if (m_Surface == EGL_NO_SURFACE)
  {
    return false;
  }

  EGLint contextAttribs[] =
  {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
  };

  m_Context = eglCreateContext(m_Display, config, EGL_NO_CONTEXT, contextAttribs);
  if (m_Context == EGL_NO_CONTEXT)
  {
    return false;
  }

  if (!eglMakeCurrent(m_Display, m_Surface, m_Surface, m_Context))
  {
    return false;
  }

  return true;
}

void AndroidGraphicsContext_OpenGLES::ShutdownGraphics()
{
  if (m_Display != EGL_NO_DISPLAY) {
    eglMakeCurrent(m_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if (m_Context != EGL_NO_CONTEXT) {
      eglDestroyContext(m_Display, m_Context);
    }
    if (m_Surface != EGL_NO_SURFACE) {
      eglDestroySurface(m_Display, m_Surface);
    }
    eglTerminate(m_Display);
  }
  m_Display = EGL_NO_DISPLAY;
  m_Context = EGL_NO_CONTEXT;
  m_Surface = EGL_NO_SURFACE;
}

void AndroidGraphicsContext_OpenGLES::Present()
{
  eglSwapBuffers(m_Display, m_Surface);
}

GraphicsContext* CreateGraphicsContext_OpenGL()
{
  return new AndroidGraphicsContext_OpenGLES();
}

ZK_NAMESPACE_END
