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

    constexpr
    EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 24,
            EGL_NONE
    };

    // The default display is probably what you want on Android
    auto display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, nullptr, nullptr);

    // figure out how many configs there are
    EGLint numConfigs;
    eglChooseConfig(display, attribs, nullptr, 0, &numConfigs);

    // get the list of configurations
    std::unique_ptr < EGLConfig[] > supportedConfigs(new EGLConfig[numConfigs]);
    eglChooseConfig(display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);

    // Find a config we like.
    // Could likely just grab the first if we don't care about anything else in the config.
    // Otherwise hook in your own heuristic
    auto config = *std::find_if(
            supportedConfigs.get(),
            supportedConfigs.get() + numConfigs,
            [&display](const EGLConfig &config) {
                EGLint red, green, blue, depth;
                if (eglGetConfigAttrib(display, config, EGL_RED_SIZE, &red)
                    && eglGetConfigAttrib(display, config, EGL_GREEN_SIZE, &green)
                    && eglGetConfigAttrib(display, config, EGL_BLUE_SIZE, &blue)
                    && eglGetConfigAttrib(display, config, EGL_DEPTH_SIZE, &depth)) {

                    return red == 8 && green == 8 && blue == 8 && depth == 24;
                }
                return false;
            });

    // create the proper window surface
    EGLint format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    EGLSurface surface = eglCreateWindowSurface(display, config, (ANativeWindow*)windowHandle, nullptr);

    // Create a GLES 3 context
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    EGLContext context = eglCreateContext(display, config, nullptr, contextAttribs);

    // get some window metrics
    auto madeCurrent = eglMakeCurrent(display, surface, surface, context);


    m_Display = display;
    m_Context = context;
    m_Surface = surface;
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
