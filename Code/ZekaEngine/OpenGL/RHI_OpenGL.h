#ifndef _H_RHI_OPENGL
#define _H_RHI_OPENGL

#include "ZekaEngine/RHIBase.h"
#include "IncludeOpenGLHeaders.h"

ZK_NAMESPACE_BEGIN

class Buffer_OpenGL : public Buffer
{
public:
  Buffer_OpenGL(BufferType type, const void* data, uint32 size, BufferFlags flags);
  ~Buffer_OpenGL();

  void SetData(const void* data, uint32 size) override;

  GLuint GetBufferID() const;
private:
  GLuint m_Buffer;
  GLenum m_BufferType;
  GLenum m_BufferFlags;
};

class Shader_OpenGL : public Shader
{  
public:
  Shader_OpenGL(const char* source, ShaderType type);
  ~Shader_OpenGL();

  GLuint GetShader() const;
private:
  GLuint m_Shader;
};

class Pipeline_OpenGL : public Pipeline
{
public:
  Pipeline_OpenGL(const PipelineDesc& desc);
  ~Pipeline_OpenGL();

  void PrepareVertexDecl();
  void PrepareShaderProgram();

  GLuint GetShaderProgram() const;
private:
  GLuint m_ShaderProgram;
};

class RenderDevice_OpenGL : public RenderDevice
{
public:
  RenderDevice_OpenGL();
  ~RenderDevice_OpenGL();

  void Clear(uint32 flags) override;
  void ClearColor(const Vector4& color) override;
  void SetVertexBuffer(Buffer* buffer) override;
  void SetIndexBuffer(Buffer* buffer) override;
  void SetPipeline(Pipeline* pipeline) override;
  void DrawArrays(PrimitiveType prim, uint32 offset, uint32 size) override;
  void DrawIndexed(PrimitiveType prim, RHIFormat format, uint32 offset, uint32 size) override;

  Buffer* CreateBuffer(BufferType type, const void* data, uint32 size, BufferFlags flags) override;
  Shader* CreateShader(const char* source, ShaderType type) override;
  Pipeline* CreatePipeline(const PipelineDesc& desc) override;
private:
  GLuint m_VertexArray;
};

ZK_NAMESPACE_END

#endif
