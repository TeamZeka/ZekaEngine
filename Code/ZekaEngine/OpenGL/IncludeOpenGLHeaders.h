#ifndef _H_INCLUDE_OPENGL_HEADERS
#define _H_INCLUDE_OPENGL_HEADERS

#if defined(ZK_PLATFORM_WINDOWS)
#define ZK_USE_OPENGL_LOADER
#endif

#if defined(ZK_USE_OPENGL_LOADER)

#include "OpenGLLoader.h"

#elif defined(ZK_PLATFORM_ANDROID)

#include <GLES3/gl3.h>

#endif

#if defined(ZK_PLATFORM_WINDOWS)

#include <gl/GL.h>

#endif

#endif
