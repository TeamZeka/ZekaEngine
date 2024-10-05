#ifndef _H_WINDOWS_GARPHICS_CONTEXT_OPENGL
#define _H_WINDOWS_GARPHICS_CONTEXT_OPENGL

#include "ZekaEngine/GraphicsContext.h"
#include "IncludeWindowsHeaders.h"

#define WGL_CONTEXT_DEBUG_BIT_ARB 0x00000001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB 0x2093
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB  0x00000002

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int* attribList);
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC) (int interval);

ZK_NAMESPACE_BEGIN

class WindowsGraphicsContext_OpenGL : public GraphicsContext
{
public:
  WindowsGraphicsContext_OpenGL();
  ~WindowsGraphicsContext_OpenGL();

  bool InitializeGraphics(void* windowHandle) override;
  void ShutdownGraphics() override;
  void Present() override;
private:
  HDC m_hDC;
  HGLRC m_Context;
};

ZK_NAMESPACE_END

#endif
