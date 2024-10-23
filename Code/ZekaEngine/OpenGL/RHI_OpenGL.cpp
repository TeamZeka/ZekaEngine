#include "RHI_OpenGL.h"
#include "ZekaEngine/Platform.h"
#include "ZekaEngine/GLSLSourceGenerator.h"

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

static uint32 GetOpenGLCullMode(CullMode mode)
{
  switch (mode)
  {
  case CullMode::Front: return GL_FRONT;
  case CullMode::Back: return GL_BACK;
  }
}

static GLenum GetOpenGLInternalPixelFormat(PixelFormat pixelFormat)
{
#if defined(ZK_OPENGLES_3_0) || defined(ZK_OPENGLES)
  switch (pixelFormat)
  {
  case PixelFormat::a8UnsignedNorm: return GL_ALPHA8_OES;
  case PixelFormat::r8UnsignedNorm: return GL_R8;
  case PixelFormat::r8SignedNorm: return GL_R8_SNORM;
  case PixelFormat::r8UnsignedInt: return GL_R8UI;
  case PixelFormat::r8SignedInt: return GL_R8I;
  case PixelFormat::r16UnsignedNorm: return GL_NONE;
  case PixelFormat::r16SignedNorm: return GL_NONE;
  case PixelFormat::r16UnsignedInt: return GL_R16UI;
  case PixelFormat::r16SignedInt: return GL_R16I;
  case PixelFormat::r16Float: return GL_R16F;
  case PixelFormat::r32UnsignedInt: return GL_R32UI;
  case PixelFormat::r32SignedInt: return GL_R32I;
  case PixelFormat::r32Float: return GL_R32F;
  case PixelFormat::rg8UnsignedNorm: return GL_RG8;
  case PixelFormat::rg8SignedNorm: return GL_RG8_SNORM;
  case PixelFormat::rg8UnsignedInt: return GL_RG8UI;
  case PixelFormat::rg8SignedInt: return GL_RG8I;
  case PixelFormat::rgba8UnsignedNorm: return GL_RGBA8;
  case PixelFormat::rgba8UnsignedNormSRGB: return GL_SRGB8_ALPHA8;
  case PixelFormat::rgba8SignedNorm: return GL_RGBA8_SNORM;
  case PixelFormat::rgba8UnsignedInt: return GL_RGBA8UI;
  case PixelFormat::rgba8SignedInt: return GL_RGBA8I;
  case PixelFormat::rgba16UnsignedNorm: return GL_NONE;
  case PixelFormat::rgba16SignedNorm: return GL_NONE;
  case PixelFormat::rgba16UnsignedInt: return GL_RGBA16UI;
  case PixelFormat::rgba16SignedInt: return GL_RGBA16I;
  case PixelFormat::rgba16Float: return GL_RGBA16F;
  case PixelFormat::rgba32UnsignedInt: return GL_RGBA32UI;
  case PixelFormat::rgba32SignedInt: return GL_RGBA32I;
  case PixelFormat::rgba32Float: return GL_RGBA32F;
  case PixelFormat::Depth: return GL_DEPTH_COMPONENT24;
  case PixelFormat::DepthStencil: return GL_DEPTH24_STENCIL8;
  }
#else
  switch (pixelFormat)
  {
  case PixelFormat::a8UnsignedNorm: return GL_ALPHA8_EXT;
  case PixelFormat::r8UnsignedNorm: return GL_R8;
  case PixelFormat::r8SignedNorm: return GL_R8_SNORM;
  case PixelFormat::r8UnsignedInt: return GL_R8UI;
  case PixelFormat::r8SignedInt: return GL_R8I;
  case PixelFormat::r16UnsignedNorm: return GL_R16;
  case PixelFormat::r16SignedNorm: return GL_R16_SNORM;
  case PixelFormat::r16UnsignedInt: return GL_R16UI;
  case PixelFormat::r16SignedInt: return GL_R16I;
  case PixelFormat::r16Float: return GL_R16F;
  case PixelFormat::r32UnsignedInt: return GL_R32UI;
  case PixelFormat::r32SignedInt: return GL_R32I;
  case PixelFormat::r32Float: return GL_R32F;
  case PixelFormat::rg8UnsignedNorm: return GL_RG8;
  case PixelFormat::rg8SignedNorm: return GL_RG8_SNORM;
  case PixelFormat::rg8UnsignedInt: return GL_RG8UI;
  case PixelFormat::rg8SignedInt: return GL_RG8I;
  case PixelFormat::rgba8UnsignedNorm: return GL_RGBA8;
  case PixelFormat::rgba8UnsignedNormSRGB: return GL_SRGB8_ALPHA8;
  case PixelFormat::rgba8SignedNorm: return GL_RGBA8_SNORM;
  case PixelFormat::rgba8UnsignedInt: return GL_RGBA8UI;
  case PixelFormat::rgba8SignedInt: return GL_RGBA8I;
  case PixelFormat::rgba16UnsignedNorm: return GL_RGBA16;
  case PixelFormat::rgba16SignedNorm: return GL_RGBA16_SNORM;
  case PixelFormat::rgba16UnsignedInt: return GL_RGBA16UI;
  case PixelFormat::rgba16SignedInt: return GL_RGBA16I;
  case PixelFormat::rgba16Float: return GL_RGBA16F;
  case PixelFormat::rgba32UnsignedInt: return GL_RGBA32UI;
  case PixelFormat::rgba32SignedInt: return GL_RGBA32I;
  case PixelFormat::rgba32Float: return GL_RGBA32F;
  case PixelFormat::Depth: return GL_DEPTH_COMPONENT24;
  case PixelFormat::DepthStencil: return GL_DEPTH24_STENCIL8;
  }
#endif

  return 0;
}

static GLenum GetOpenGLPixelFormat(PixelFormat pixelFormat)
{
  switch (pixelFormat)
  {
  case PixelFormat::a8UnsignedNorm: return GL_ALPHA;
  case PixelFormat::r8UnsignedNorm:
  case PixelFormat::r8SignedNorm:
  case PixelFormat::r16UnsignedNorm:
  case PixelFormat::r16SignedNorm:
  case PixelFormat::r16Float:
  case PixelFormat::r32Float: return GL_RED;
  case PixelFormat::r8UnsignedInt:
  case PixelFormat::r8SignedInt:
  case PixelFormat::r16UnsignedInt:
  case PixelFormat::r16SignedInt:
  case PixelFormat::r32UnsignedInt:
  case PixelFormat::r32SignedInt: return GL_RED_INTEGER;
  case PixelFormat::rg8UnsignedNorm:
  case PixelFormat::rg8SignedNorm: return GL_RG;
  case PixelFormat::rg8UnsignedInt:
  case PixelFormat::rg8SignedInt: return GL_RG_INTEGER;
  case PixelFormat::rgba8UnsignedNorm:
  case PixelFormat::rgba8UnsignedNormSRGB:
  case PixelFormat::rgba8SignedNorm:
  case PixelFormat::rgba16UnsignedNorm:
  case PixelFormat::rgba16SignedNorm:
  case PixelFormat::rgba16Float:
  case PixelFormat::rgba32Float: return GL_RGBA;
  case PixelFormat::rgba8UnsignedInt:
  case PixelFormat::rgba8SignedInt:
  case PixelFormat::rgba16UnsignedInt:
  case PixelFormat::rgba16SignedInt:
  case PixelFormat::rgba32UnsignedInt:
  case PixelFormat::rgba32SignedInt: return GL_RGBA_INTEGER;
  case PixelFormat::Depth: return GL_DEPTH_COMPONENT;
  case PixelFormat::DepthStencil: return GL_DEPTH_STENCIL;
  }

  return 0;
}

uint32 TextureWrapToGL(const TextureWrap wrap)
{
  switch (wrap)
  {
#ifndef ZK_PLATFORM_ANDROID
  case TextureWrap::Clamp: return GL_CLAMP;
  case TextureWrap::ClampToBorder: return GL_CLAMP_TO_BORDER;
#else
  case TextureWrap::Clamp: return GL_CLAMP_TO_EDGE;
#endif
  case TextureWrap::ClampToEdge: return GL_CLAMP_TO_EDGE;
  case TextureWrap::Repeat: return GL_REPEAT;
  case TextureWrap::MirroredRepeat: return GL_MIRRORED_REPEAT;
  }

  return 0;
}

static GLenum GetOpenGLPixelType(PixelFormat pixelFormat)
{
  switch (pixelFormat)
  {
  case PixelFormat::a8UnsignedNorm:
  case PixelFormat::r8UnsignedNorm:
  case PixelFormat::r16UnsignedNorm:
  case PixelFormat::rg8UnsignedNorm:
  case PixelFormat::rgba8UnsignedNorm:
  case PixelFormat::rgba8UnsignedNormSRGB:
  case PixelFormat::rgba16UnsignedNorm: return GL_UNSIGNED_BYTE;
  case PixelFormat::r8SignedNorm:
  case PixelFormat::r16SignedNorm:
  case PixelFormat::rg8SignedNorm:
  case PixelFormat::rgba8SignedNorm:
  case PixelFormat::rgba16SignedNorm: return GL_BYTE;
  case PixelFormat::r8UnsignedInt:
  case PixelFormat::r16UnsignedInt:
  case PixelFormat::r32UnsignedInt:
  case PixelFormat::rg8UnsignedInt:
  case PixelFormat::rgba8UnsignedInt:
  case PixelFormat::rgba16UnsignedInt:
  case PixelFormat::rgba32UnsignedInt: return GL_UNSIGNED_INT;
  case PixelFormat::r8SignedInt:
  case PixelFormat::r16SignedInt:
  case PixelFormat::r32SignedInt:
  case PixelFormat::rg8SignedInt:
  case PixelFormat::rgba8SignedInt:
  case PixelFormat::rgba16SignedInt:
  case PixelFormat::rgba32SignedInt: return GL_INT;
  case PixelFormat::r16Float:
  case PixelFormat::r32Float:
  case PixelFormat::rgba16Float:
  case PixelFormat::rgba32Float:
  case PixelFormat::Depth: return GL_UNSIGNED_INT;
  case PixelFormat::DepthStencil: return GL_UNSIGNED_INT_24_8;
  }

  return 0;
}

static GLenum GetOpenGLComparisonFunc(ComparisonFunc func)
{
  switch (func)
  {
  case Zeka::ComparisonFunc::Never: return GL_NEVER;
  case Zeka::ComparisonFunc::Less: return GL_LESS;
  case Zeka::ComparisonFunc::Equal: return GL_EQUAL;
  case Zeka::ComparisonFunc::LessEqual: return GL_LEQUAL;
  case Zeka::ComparisonFunc::Greater: return GL_GREATER;
  case Zeka::ComparisonFunc::NotEqual: return GL_NOTEQUAL;
  case Zeka::ComparisonFunc::GreaterEqual: return GL_GEQUAL;
  case Zeka::ComparisonFunc::Always: return GL_ALWAYS;
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
  case BufferType::Uniform: m_BufferType = GL_UNIFORM_BUFFER; break;
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

  GLSLSourceGenerator sourceGen;
  const std::string processedSource = sourceGen.GenerateSource(source);
  const char* pSrc = processedSource.c_str();

  m_Shader = glCreateShader(gl_type);
  glShaderSource(m_Shader, 1, &pSrc, NULL);
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

Texture_OpenGL::Texture_OpenGL(PixelFormat format, uint32 width, uint32 height, const void* data)
  : Texture(format, width, height, data)
{
  glGenTextures(1, &m_Texture);
  glBindTexture(GL_TEXTURE_2D, m_Texture);
  
  GLenum gl_format = GetOpenGLPixelFormat(format);
  GLenum gl_internalFormat = GetOpenGLInternalPixelFormat(format);
  
  glTexImage2D(GL_TEXTURE_2D, 0, gl_internalFormat, width, height, 0, gl_format, GetOpenGLPixelType(format), data ? data : NULL);
}

Texture_OpenGL::~Texture_OpenGL()
{
  glDeleteTextures(1, &m_Texture);
}

void Texture_OpenGL::SetMinFilter(TextureFilter filter)
{
  glBindTexture(GL_TEXTURE_2D, m_Texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter == TextureFilter::Linear ? GL_LINEAR : GL_NEAREST);
}

void Texture_OpenGL::SetMagFilter(TextureFilter filter)
{
  glBindTexture(GL_TEXTURE_2D, m_Texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter == TextureFilter::Linear ? GL_LINEAR : GL_NEAREST);
}

void Texture_OpenGL::SetWrapT(TextureWrap wrap)
{
  glBindTexture(GL_TEXTURE_2D, m_Texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToGL(wrap));
}

void Texture_OpenGL::SetWrapS(TextureWrap wrap)
{
  glBindTexture(GL_TEXTURE_2D, m_Texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToGL(wrap));
}

void Texture_OpenGL::SetWrapR(TextureWrap wrap)
{
  glBindTexture(GL_TEXTURE_2D, m_Texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, TextureWrapToGL(wrap));
}

GLuint Texture_OpenGL::GetTexture() const
{
  return m_Texture;
}

RenderDevice_OpenGL::RenderDevice_OpenGL()
{
  glGenVertexArrays(1, &m_VertexArray);
  glBindVertexArray(m_VertexArray);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
}

RenderDevice_OpenGL::~RenderDevice_OpenGL()
{
  glDeleteVertexArrays(1, &m_VertexArray);
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

void RenderDevice_OpenGL::SetUniformBuffer(Buffer* buffer, uint32 id)
{
  Buffer_OpenGL* gl_buffer = static_cast<Buffer_OpenGL*>(buffer);
  if (gl_buffer)
  {
    glBindBufferBase(GL_UNIFORM_BUFFER, id, gl_buffer->GetBufferID());
  }
  else
  {
    glBindBufferBase(GL_UNIFORM_BUFFER, id, 0);
  }
}

void RenderDevice_OpenGL::SetPipeline(Pipeline* pipeline)
{
  Pipeline_OpenGL* gl_pp = static_cast<Pipeline_OpenGL*>(pipeline);
  m_CurrentGLPipeline = gl_pp;
  if (gl_pp)
  {
    const PipelineDesc desc = gl_pp->GetDesc();

    glUseProgram(gl_pp->GetShaderProgram());

    gl_pp->PrepareVertexDecl();
    if (desc.BlendingEnable)
    {
      glEnable(GL_BLEND);
      glBlendEquation(GL_FUNC_ADD);

      const BlendMode blendMode = desc.BlendMode;
      if (blendMode == BlendMode::SrcAlphaOneMinusSrcAlpha)
      {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      }
      else if (blendMode == BlendMode::ZeroSrcColor)
      {
        glBlendFunc(GL_ZERO, GL_SRC_COLOR);
      }
      else if (blendMode == BlendMode::OneZero)
      {
        glBlendFunc(GL_ONE, GL_ZERO);
      }
      else if (blendMode == BlendMode::OneMinusSrcAlpha)
      {
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
      }
      else
      {
        glBlendFunc(GL_NONE, GL_NONE);
      }
    }
    else
    {
      glDisable(GL_BLEND);
    }

    const CullMode cullMode = desc.CullMode;
    if (cullMode != CullMode::Normal)
    {
      glEnable(GL_CULL_FACE);
      glCullFace(GetOpenGLCullMode(cullMode));
    }
    else
    {
      glDisable(GL_CULL_FACE);
    }

    if (desc.DepthEnable)
    {
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GetOpenGLComparisonFunc(desc.DepthFunc));
    }
    else
    {
      glDisable(GL_DEPTH_TEST);
    }
  }
  else
  {
    glUseProgram(0);
  }
}

void RenderDevice_OpenGL::SetTexture(Texture* texture, uint32 slot)
{
  Texture_OpenGL* gl_tex = static_cast<Texture_OpenGL*>(texture);
  glActiveTexture(GL_TEXTURE0 + slot);
  if (gl_tex)
  {
    glBindTexture(GL_TEXTURE_2D, gl_tex->GetTexture());
  }
  else
  {
    glBindTexture(GL_TEXTURE_2D, 0);
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

Texture* RenderDevice_OpenGL::CreateTexture(PixelFormat format, uint32 width, uint32 height, const void* data)
{
  return new Texture_OpenGL(format, width, height, data);
}

RenderDevice* CreateRenderDevice_OpenGL(GraphicsContext* context)
{
  return new RenderDevice_OpenGL();
}

ZK_NAMESPACE_END
