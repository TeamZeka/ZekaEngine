#include "GLSLSourceGenerator.h"
#include "Platform.h"

ZK_NAMESPACE_BEGIN

GLSLSourceGenerator::GLSLSourceGenerator()
{
}

GLSLSourceGenerator::~GLSLSourceGenerator()
{
}

const std::string GLSLSourceGenerator::GenerateSource(const char* mainSource)
{
#if defined(ZK_OPENGLES_3_0) || defined(ZK_OPENGLES)
  Append("#version 300 es\n");
#else
  Append("#version 330\n");
#endif

#if defined(ZK_OPENGLES)
  Append("#define ZK_OPENGLES\n");
#if defined(ZK_OPENGLES_3_0)
  Append("#define ZK_OPENGLES_3_0\n");
#endif
#else
  Append("#define ZK_OPENGL\n");
#endif

#if defined(ZK_PLATFORM_ANDROID)
  Append("#define ZK_PLATFORM_ANDROID\n");
#elif defined(ZK_PLATFORM_WINDOWS)
  Append("#define ZK_PLATFORM_WINDOWS\n");
#endif

  Append(mainSource);
  return m_Stream.str();
}

void GLSLSourceGenerator::Append(const std::string& line)
{
  m_Stream << line;
}

ZK_NAMESPACE_END
