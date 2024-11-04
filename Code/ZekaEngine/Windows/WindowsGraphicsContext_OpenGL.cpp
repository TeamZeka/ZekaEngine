#include "WindowsGraphicsContext_OpenGL.h"
#include "ZekaEngine/OpenGL/OpenGLLoader.h"

ZK_NAMESPACE_BEGIN

static struct
{
  PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
  PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
} s_WindowContextInfo;

WindowsGraphicsContext_OpenGL::WindowsGraphicsContext_OpenGL()
{
}

WindowsGraphicsContext_OpenGL::~WindowsGraphicsContext_OpenGL()
{
}

bool WindowsGraphicsContext_OpenGL::InitializeGraphics(void* windowHandle)
{
  m_WindowHandle = windowHandle;

  m_hDC = GetDC((HWND)windowHandle);

  PIXELFORMATDESCRIPTOR pfd = {};
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 24;
  pfd.cStencilBits = 8;
  pfd.cAuxBuffers = 0;
  pfd.iLayerType = PFD_MAIN_PLANE;

  int32 pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
  if (pixelFormat) 
  {
    if (SetPixelFormat(m_hDC, pixelFormat, &pfd) == FALSE) 
    {
      return false;
    }
  }

  HGLRC tempContext = wglCreateContext(m_hDC);
  wglMakeCurrent(m_hDC, tempContext);

  s_WindowContextInfo.wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
  s_WindowContextInfo.wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

  const int contextAttribsList[] = {
      WGL_CONTEXT_MAJOR_VERSION_ARB,
      4,
      WGL_CONTEXT_MINOR_VERSION_ARB,
      4,
      WGL_CONTEXT_PROFILE_MASK_ARB,
      WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifdef SPA_DEBUG
      WGL_CONTEXT_FLAGS_ARB,
      WGL_CONTEXT_DEBUG_BIT_ARB,
#else
      WGL_CONTEXT_FLAGS_ARB,
      0,
#endif
      0,
  };

  m_Context = s_WindowContextInfo.wglCreateContextAttribsARB(m_hDC, nullptr, contextAttribsList);
  if (wglMakeCurrent(m_hDC, m_Context) == FALSE)
  {
    return false;
  }

  if (!OpenGLLoader::Initialize())
  {
    return false;
  }

  return true;
}

void WindowsGraphicsContext_OpenGL::ShutdownGraphics()
{
  OpenGLLoader::Shutdown();
}

void WindowsGraphicsContext_OpenGL::Present()
{
  SwapBuffers(m_hDC);
}

void WindowsGraphicsContext_OpenGL::SetVSync(bool vsync)
{
  if (m_IsVSync != vsync)
  {
    m_IsVSync = vsync;
    
    s_WindowContextInfo.wglSwapIntervalEXT(vsync ? 1 : 0);
  }
}

GraphicsContext* GraphicsContext::Create_OpenGL()
{
  return new WindowsGraphicsContext_OpenGL();
}

ZK_NAMESPACE_END
