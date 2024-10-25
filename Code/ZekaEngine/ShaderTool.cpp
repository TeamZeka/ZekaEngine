#include "ShaderTool.h"
#include "Platform.h"
#include "Encryption.h"

ZK_NAMESPACE_BEGIN

Shader* ShaderTool::ImportShader(RenderDevice* device, const char* filename, ShaderType type)
{
  File* file = OpenFile(filename, FileAccess::Read);
  const uint32 size = file->GetSize();

  char* data = new char[size + 1];
  data[size] = 0;
  file->Read(data, size);
  file->Close();

  return device->CreateShader(data, type);
}

void ShaderTool::SaveShader(File* stream, const char* source, uint32 size, ShaderType type)
{
  stream->Write(&size, sizeof(uint32));
  stream->Write(&type, sizeof(ShaderType));

  char* memory = new char[size + 1];
  memcpy(memory, source, size);

  Encryption::DecryptBytes((uint8*)memory, size);
  memory[size] = 0;

  stream->Write(memory, size);
}

Shader* ShaderTool::ImportShader(RenderDevice* device, File* stream)
{
  uint32 size = 0;
  stream->Read(&size, sizeof(uint32));

  ShaderType type;
  stream->Read(&type, sizeof(ShaderType));

  char* memory = new char[size + 1];
  stream->Read(memory, size);
  
  Encryption::EncryptBytes((uint8*)memory, size);
  memory[size] = 0;

  return device->CreateShader(memory, type);
}

ZK_NAMESPACE_END
