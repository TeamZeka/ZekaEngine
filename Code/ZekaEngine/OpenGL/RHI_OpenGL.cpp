#include "RHI_OpenGL.h"
#include "ZekaEngine/Platform.h"

ZK_NAMESPACE_BEGIN

static uint32 GetRHIFormatOpenGLType(RHIFormat format)
{
  switch (format)
  {
  case RHIFormat::Float32:
  case RHIFormat::Float32Vector2: 
  case RHIFormat::Float32Vector3: 
  case RHIFormat::Float32Vector4: 
  case RHIFormat::Float32Matrix4: return GL_FLOAT;

  case RHIFormat::Int32:
  case RHIFormat::Int32Vector2:
  case RHIFormat::Int32Vector3:
  case RHIFormat::Int32Vector4: return GL_INT;

  case RHIFormat::UInt32:
  case RHIFormat::UInt32Vector2:
  case RHIFormat::UInt32Vector3:
  case RHIFormat::UInt32Vector4: return GL_UNSIGNED_INT;

  case RHIFormat::Int16:
  case RHIFormat::Int16Norm:
  case RHIFormat::Int16Vector2:
  case RHIFormat::Int16Vector2Norm:
  case RHIFormat::Int16Vector3:
  case RHIFormat::Int16Vector3Norm:
  case RHIFormat::Int16Vector4:
  case RHIFormat::Int16Vector4Norm: return GL_SHORT;

  case RHIFormat::UInt16:
  case RHIFormat::UInt16Norm:
  case RHIFormat::UInt16Vector2:
  case RHIFormat::UInt16Vector2Norm:
  case RHIFormat::UInt16Vector3:
  case RHIFormat::UInt16Vector3Norm: 
  case RHIFormat::UInt16Vector4:
  case RHIFormat::UInt16Vector4Norm: return GL_UNSIGNED_SHORT;

  case RHIFormat::Byte:
  case RHIFormat::ByteNorm:
  case RHIFormat::ByteVector2:
  case RHIFormat::ByteVector2Norm:
  case RHIFormat::ByteVector3:
  case RHIFormat::ByteVector3Norm:
  case RHIFormat::ByteVector4:
  case RHIFormat::ByteVector4Norm: return GL_BYTE;

  case RHIFormat::UByte:
  case RHIFormat::UByteNorm:
  case RHIFormat::UByteVector2:
  case RHIFormat::UByteVector2Norm:
  case RHIFormat::UByteVector3:
  case RHIFormat::UByteVector3Norm:
  case RHIFormat::UByteVector4:
  case RHIFormat::UByteVector4Norm: return GL_UNSIGNED_BYTE;
  }

  return 0;
}

static uint32 GetOpenGLPrimitiveType(PrimitiveType type)
{
  switch (type)
  {
  case PrimitiveType::TriangleList: return GL_TRIANGLES;
  case PrimitiveType::LineList: return GL_LINES;
  case PrimitiveType::PointList: return GL_POINTS;
  case PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
  case PrimitiveType::LineStrip: return GL_LINE_STRIP;
  case PrimitiveType::TriangleFan: return GL_TRIANGLE_FAN;
  }

  return 0;
}

Buffer_OpenGL::Buffer_OpenGL(BufferType type, const void* data, uint32 size, BufferFlags flags)
  : Buffer(type, data, size, flags)
{
  switch (type)
  {
  case BufferType::Index: m_BufferType = GL_ELEMENT_ARRAY_BUFFER; break;
  case BufferType::Vertex: m_BufferType = GL_ARRAY_BUFFER; break;
  }

  switch (flags)
  {
  case BufferFlags::Dynamic: m_BufferFlags = GL_DYNAMIC_DRAW; break;
  case BufferFlags::Static: m_BufferFlags = GL_STATIC_DRAW; break;
  }

  glGenBuffers(1, &m_Buffer);
  glBindBuffer(m_BufferType, m_Buffer);
  glBufferData(m_BufferType, size, data, m_BufferFlags);
}

Buffer_OpenGL::~Buffer_OpenGL()
{
  glDeleteBuffers(1, &m_Buffer);
}

void Buffer_OpenGL::SetData(const void* data, uint32 size)
{
  glBindBuffer(m_BufferType, m_Buffer);
  if (size > m_Size)
  {
    glBufferData(m_BufferType, size, data, GL_DYNAMIC_DRAW);
  }
  else
  {
    glBufferSubData(m_BufferType, 0, size, data);
  }
}

GLuint Buffer_OpenGL::GetBufferID() const
{
  return m_Buffer;
}

Shader_OpenGL::Shader_OpenGL(const char* source, ShaderType type)
  : Shader(source, type)
{
  GLenum gl_type = 0;
  switch (type)
  {
  case ShaderType::Vertex: gl_type = GL_VERTEX_SHADER; break;
  case ShaderType::Fragment: gl_type = GL_FRAGMENT_SHADER; break;
  }

  m_Shader = glCreateShader(gl_type);
  glShaderSource(m_Shader, 1, &source, NULL);
  glCompileShader(m_Shader);

  GLint shaderCompiled = 0;
  glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &shaderCompiled);

  if (!shaderCompiled)
  {
    GLint infoLength = 0;
    glGetShaderiv(m_Shader, GL_INFO_LOG_LENGTH, &infoLength);

    if (infoLength)
    {
      auto *infoLog = new GLchar[infoLength];
      glGetShaderInfoLog(m_Shader, infoLength, nullptr, infoLog);
      Platform::Log(Platform::LogLevel::Error, infoLog);
      delete[] infoLog;
    }

    glDeleteShader(m_Shader);
    m_Shader = 0;
  }
}

Shader_OpenGL::~Shader_OpenGL()
{
  glDeleteShader(m_Shader);
}

GLuint Shader_OpenGL::GetShader() const
{
  return m_Shader;
}

Pipeline_OpenGL::Pipeline_OpenGL(const PipelineDesc& desc)
  : Pipeline(desc)
{
  PrepareShaderProgram();
}

Pipeline_OpenGL::~Pipeline_OpenGL()
{
  glDeleteProgram(m_ShaderProgram);
}

void Pipeline_OpenGL::PrepareVertexDecl()
{
  for (uint32 i = 0; i < m_Desc.VertexDecl.Elements.size(); i++)
  {
    const auto element = m_Desc.VertexDecl.Elements[i];

    glVertexAttribPointer(i, element.Count, GetRHIFormatOpenGLType(element.Format), 
      GL_FALSE, m_Desc.VertexDecl.Stride, (const void*)element.Offset);
    glEnableVertexAttribArray(i);
  }
}

void Pipeline_OpenGL::PrepareShaderProgram()
{
  m_ShaderProgram = glCreateProgram();

  Shader_OpenGL* vs = static_cast<Shader_OpenGL*>(m_Desc.VertexShader);
  Shader_OpenGL* fs = static_cast<Shader_OpenGL*>(m_Desc.FragmentShader);

  if (vs)
  {
    glAttachShader(m_ShaderProgram, vs->GetShader());
  }

  if (fs)
  {
    glAttachShader(m_ShaderProgram, fs->GetShader());
  }

  glLinkProgram(m_ShaderProgram);

  GLint linkStatus = GL_FALSE;
  glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &linkStatus);
  if (linkStatus != GL_TRUE)
  {
    GLint logLength = 0;
    glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength)
    {
      GLchar *log = new GLchar[logLength];
      glGetProgramInfoLog(m_ShaderProgram, logLength, nullptr, log);
      Platform::Log(Platform::LogLevel::Error, log);
      delete[] log;
    }

    glDeleteProgram(m_ShaderProgram);
  }

  if (vs)
  {
    glDetachShader(m_ShaderProgram, vs->GetShader());
  }

  if (fs)
  {
    glDetachShader(m_ShaderProgram, fs->GetShader());
  }
}

GLuint Pipeline_OpenGL::GetShaderProgram() const
{
  return m_ShaderProgram;
}

RenderDevice_OpenGL::RenderDevice_OpenGL()
{
  glGenVertexArrays(1, &m_VertexArray);
  glBindVertexArray(m_VertexArray);
}

RenderDevice_OpenGL::~RenderDevice_OpenGL()
{
}

void RenderDevice_OpenGL::Clear(uint32 flags)
{
  GLenum mask = 0;
  if (flags & ClearFlags::ClearColor)
  {
    mask |= GL_COLOR_BUFFER_BIT;
  }
  if (flags & ClearFlags::ClearDepth)
  {
    mask |= GL_DEPTH_BUFFER_BIT;
  }
  if (flags & ClearFlags::ClearStencil)
  {
    mask |= GL_STENCIL_BUFFER_BIT;
  }
  glClear(mask);
}

void RenderDevice_OpenGL::ClearColor(const Vector4& color)
{
  glClearColor(color.X, color.Y, color.Z, color.W);
}

void RenderDevice_OpenGL::SetVertexBuffer(Buffer* buffer)
{
  Buffer_OpenGL* gl_buffer = static_cast<Buffer_OpenGL*>(buffer);
  if (gl_buffer)
  {
    glBindBuffer(GL_ARRAY_BUFFER, gl_buffer->GetBufferID());
  }
  else
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
}

void RenderDevice_OpenGL::SetIndexBuffer(Buffer* buffer)
{
  Buffer_OpenGL* gl_buffer = static_cast<Buffer_OpenGL*>(buffer);
  if (gl_buffer)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_buffer->GetBufferID());
  }
  else
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}

void RenderDevice_OpenGL::SetPipeline(Pipeline* pipeline)
{
  Pipeline_OpenGL* gl_pp = static_cast<Pipeline_OpenGL*>(pipeline);
  if (gl_pp)
  {
    glUseProgram(gl_pp->GetShaderProgram());

    gl_pp->PrepareVertexDecl();
  }
  else
  {
    glUseProgram(0);
  }
}

void RenderDevice_OpenGL::DrawArrays(PrimitiveType prim, uint32 offset, uint32 size)
{
  GLenum gl_prim = GetOpenGLPrimitiveType(prim);

  glDrawArrays(gl_prim, offset, size);
}

void RenderDevice_OpenGL::DrawIndexed(PrimitiveType prim, RHIFormat format, uint32 offset, uint32 size)
{
  GLenum gl_format = GetRHIFormatOpenGLType(format);
  GLenum gl_prim = GetOpenGLPrimitiveType(prim);

  glDrawElements(gl_prim, size, gl_format, (const void*)offset);
}

Buffer* RenderDevice_OpenGL::CreateBuffer(BufferType type, const void* data, uint32 size, BufferFlags flags)
{
  return new Buffer_OpenGL(type, data, size, flags);
}

Shader* RenderDevice_OpenGL::CreateShader(const char* source, ShaderType type)
{
  return new Shader_OpenGL(source, type);
}

Pipeline* RenderDevice_OpenGL::CreatePipeline(const PipelineDesc& desc)
{
  return new Pipeline_OpenGL(desc);
}

RenderDevice* CreateRenderDevice_OpenGL(GraphicsContext* context)
{
  return new RenderDevice_OpenGL();
}

ZK_NAMESPACE_END
