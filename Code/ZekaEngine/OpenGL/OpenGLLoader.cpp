#include "OpenGLLoader.h"
#include "ZekaEngine/Platform.h"

#define ZK_GL_FUNCTION(type, name) type name;
#include "OpenGLFunctions.h"
#undef ZK_GL_FUNCTION

ZK_NAMESPACE_BEGIN

namespace OpenGLLoader
{
	static struct
	{
		void* GLModule = nullptr;
	} s_LoaderData;

	static void* _GLGetFunction(const char* name)
	{
		void* p = Platform::GetGLProcAddress(name);
		if (p == nullptr)
			p = Platform::GetProcAddress(s_LoaderData.GLModule, name);

		return p;
	}

	bool Initialize()
	{
#ifdef ZK_PLATFORM_WINDOWS
		s_LoaderData.GLModule = Platform::LoadModule("opengl32.dll");
#endif

    if (s_LoaderData.GLModule == nullptr)
    {
      return false;
    }

#define ZK_GL_FUNCTION(type, name) name = (type)_GLGetFunction(#name); if (name == NULL) { OutputDebugStringA("tst\n"); return false; }
#include "OpenGLFunctions.h"
#undef ZK_GL_FUNCTION

    Platform::FreeLibrary(s_LoaderData.GLModule);
		return true;
	}

	void Shutdown()
	{
	}
}

ZK_NAMESPACE_END
