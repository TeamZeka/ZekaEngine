#ifndef _H_OPENGL_LOADER
#define _H_OPENGL_LOADER

#include "ZekaEngine/HelperDefines.h"

#include "glcorearb.h"

#define ZK_GL_FUNCTION(type, name) GLAPI type name;
#include "OpenGLFunctions.h"
#undef ZK_GL_FUNCTION

ZK_NAMESPACE_BEGIN

namespace OpenGLLoader
{
	bool Initialize();
	void Shutdown();
}

ZK_NAMESPACE_END

#endif
