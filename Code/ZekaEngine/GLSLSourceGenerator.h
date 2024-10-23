#ifndef _H_GLSL_SOURCE_GENERATOR
#define _H_GLSL_SOURCE_GENERATOR

#include "HelperDefines.h"

#include <sstream>

ZK_NAMESPACE_BEGIN

class GLSLSourceGenerator
{
public:
  GLSLSourceGenerator();
  ~GLSLSourceGenerator();

  const std::string GenerateSource(const char* mainSource);
private:
  void Append(const std::string& line);
private:
  std::stringstream m_Stream;
};

ZK_NAMESPACE_END

#endif
