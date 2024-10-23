#ifndef _H_SHADER_TOOL
#define _H_SHADER_TOOL

#include "RHIBase.h"
#include "FileSystem.h"

ZK_NAMESPACE_BEGIN

class ShaderTool
{
public:
  static Shader* ImportShader(RenderDevice* device, const char* filename, ShaderType type);
  
  static void SaveShader(File* stream, const char* source, uint32 size, ShaderType type);
  static Shader* ImportShader(RenderDevice* device, File* stream);
};

ZK_NAMESPACE_END

#endif
