#ifndef _H_RHI_BASE
#define _H_RHI_BASE

#include "Vector4.h"
#include "GraphicsContext.h"

#include <vector>

ZK_NAMESPACE_BEGIN

namespace ClearFlags
{
  enum : uint32
  {
    ClearColor = 1 << 0,
    ClearDepth = 1 << 1,
    ClearStencil = 1 << 2
  };
}

enum class BufferType : uint32
{
  Index = 0,
  Vertex,
  Uniform
};

enum class BufferFlags : uint32
{
  Dynamic = 0,
  Static
};

class Buffer
{
public:
  Buffer(BufferType type, const void* data, uint32 size, BufferFlags flags) 
    : m_Type(type)
    , m_Flags(flags)
    , m_Size(size) 
  {}
  ~Buffer() {}

  virtual void SetData(const void* data, uint32 size) = 0;

  BufferType GetBufferType() const { return m_Type; }
  BufferFlags GetBufferFlags() const { return m_Flags; }
  uint32 GetSize() const { return m_Size; }
protected:
  BufferType m_Type;
  BufferFlags m_Flags;
  uint32 m_Size;
};

enum class ShaderType : uint32
{
  Vertex = 0,
  Fragment
};

class Shader
{
public:
  Shader(const char* source, ShaderType type) : m_Type(type) {}
  ~Shader() {}

  ShaderType GetType() const { return m_Type; }
protected:
  ShaderType m_Type;
};

enum class RHIFormat : uint32
{
  Float32 = 0,
  Float32Vector2,
  Float32Vector3,
  Float32Vector4,
  Float32Matrix4,

  UInt32,
  UInt32Vector2,
  UInt32Vector3,
  UInt32Vector4,

  Int32,
  Int32Vector2,
  Int32Vector3,
  Int32Vector4,

  UInt16,
  UInt16Vector2,
  UInt16Vector3,
  UInt16Vector4,

  Int16,
  Int16Vector2,
  Int16Vector3,
  Int16Vector4,

  UInt16Norm,
  UInt16Vector2Norm,
  UInt16Vector3Norm,
  UInt16Vector4Norm,

  Int16Norm,
  Int16Vector2Norm,
  Int16Vector3Norm,
  Int16Vector4Norm,

  Byte,
  ByteNorm,
  UByte,
  UByteNorm,

  ByteVector2,
  ByteVector2Norm,
  UByteVector2,
  UByteVector2Norm,

  ByteVector3,
  ByteVector3Norm,
  UByteVector3,
  UByteVector3Norm,

  ByteVector4,
  ByteVector4Norm,
  UByteVector4,
  UByteVector4Norm
};

inline uint32 GetRHIFormatCount(RHIFormat format)
{
  switch (format)
  {
  case RHIFormat::Float32:
  case RHIFormat::Int32:
  case RHIFormat::UInt32:
  case RHIFormat::Int16:
  case RHIFormat::Int16Norm:
  case RHIFormat::UInt16:
  case RHIFormat::UInt16Norm:
  case RHIFormat::Byte:
  case RHIFormat::ByteNorm:
  case RHIFormat::UByte:
  case RHIFormat::UByteNorm: return 1;

  case RHIFormat::Float32Vector2:
  case RHIFormat::Int32Vector2:
  case RHIFormat::UInt32Vector2:
  case RHIFormat::Int16Vector2:
  case RHIFormat::Int16Vector2Norm:
  case RHIFormat::UInt16Vector2:
  case RHIFormat::UInt16Vector2Norm:
  case RHIFormat::ByteVector2:
  case RHIFormat::ByteVector2Norm:
  case RHIFormat::UByteVector2:
  case RHIFormat::UByteVector2Norm: return 2;

  case RHIFormat::Float32Vector3:
  case RHIFormat::Int32Vector3:
  case RHIFormat::UInt32Vector3:
  case RHIFormat::Int16Vector3:
  case RHIFormat::Int16Vector3Norm:
  case RHIFormat::UInt16Vector3:
  case RHIFormat::UInt16Vector3Norm:
  case RHIFormat::ByteVector3:
  case RHIFormat::ByteVector3Norm:
  case RHIFormat::UByteVector3:
  case RHIFormat::UByteVector3Norm: return 3;

  case RHIFormat::Float32Vector4:
  case RHIFormat::Int32Vector4:
  case RHIFormat::UInt32Vector4:
  case RHIFormat::Int16Vector4:
  case RHIFormat::Int16Vector4Norm:
  case RHIFormat::UInt16Vector4:
  case RHIFormat::UInt16Vector4Norm:
  case RHIFormat::ByteVector4:
  case RHIFormat::ByteVector4Norm:
  case RHIFormat::UByteVector4:
  case RHIFormat::UByteVector4Norm: return 4;

  case RHIFormat::Float32Matrix4: return 16;
  }

  return 0;
}

inline uint32 GetRHIFormatSize(RHIFormat format)
{
  switch (format)
  {
  case RHIFormat::Float32: return sizeof(float);
  case RHIFormat::Float32Vector2: return 2 * sizeof(float);
  case RHIFormat::Float32Vector3: return 3 * sizeof(float);
  case RHIFormat::Float32Vector4: return 4 * sizeof(float);
  case RHIFormat::Float32Matrix4: return 16 * sizeof(float);

  case RHIFormat::Int32:
  case RHIFormat::UInt32: return sizeof(uint32);
  case RHIFormat::Int32Vector2:
  case RHIFormat::UInt32Vector2: return 2 * sizeof(uint32);
  case RHIFormat::Int32Vector3:
  case RHIFormat::UInt32Vector3: return 3 * sizeof(uint32);
  case RHIFormat::Int32Vector4:
  case RHIFormat::UInt32Vector4: return 4 * sizeof(uint32);

  case RHIFormat::Int16:
  case RHIFormat::Int16Norm:
  case RHIFormat::UInt16:
  case RHIFormat::UInt16Norm: return sizeof(uint16);

  case RHIFormat::Int16Vector2:
  case RHIFormat::Int16Vector2Norm:
  case RHIFormat::UInt16Vector2:
  case RHIFormat::UInt16Vector2Norm: return 2 * sizeof(uint16);

  case RHIFormat::Int16Vector3:
  case RHIFormat::Int16Vector3Norm:
  case RHIFormat::UInt16Vector3:
  case RHIFormat::UInt16Vector3Norm: return 3 * sizeof(uint16);

  case RHIFormat::Int16Vector4:
  case RHIFormat::Int16Vector4Norm:
  case RHIFormat::UInt16Vector4:
  case RHIFormat::UInt16Vector4Norm: return 4 * sizeof(uint16);

  case RHIFormat::Byte:
  case RHIFormat::ByteNorm:
  case RHIFormat::UByte:
  case RHIFormat::UByteNorm: return sizeof(uint8);

  case RHIFormat::ByteVector2:
  case RHIFormat::ByteVector2Norm:
  case RHIFormat::UByteVector2:
  case RHIFormat::UByteVector2Norm: return 2 * sizeof(uint8);

  case RHIFormat::ByteVector3:
  case RHIFormat::ByteVector3Norm:
  case RHIFormat::UByteVector3:
  case RHIFormat::UByteVector3Norm: return 3 * sizeof(uint8);

  case RHIFormat::ByteVector4:
  case RHIFormat::ByteVector4Norm:
  case RHIFormat::UByteVector4:
  case RHIFormat::UByteVector4Norm: return 4 * sizeof(uint8);
  }

  return 0;
}

struct VertexDecl
{
  struct Element
  {
    RHIFormat Format;
    uint32 Offset;
    uint32 Count;
  };

  VertexDecl() : Stride(0) {}
  ~VertexDecl() {}

  void PushElement(RHIFormat format)
  {
    Element element;
    element.Format = format;
    element.Offset = Stride;
    element.Count = GetRHIFormatCount(format);
    Elements.push_back(element);

    Stride += GetRHIFormatSize(format);
  }

  uint32 GetStride() const
  {
    return Stride;
  }

  std::vector<Element> Elements;
  uint32 Stride;
};

enum class CullMode : uint32
{
  Normal = 0,
  Front,
  Back
};

enum class BlendMode : uint32
{
  OneZero = 0,
  ZeroSrcColor,
  OneMinusSrcAlpha,
  SrcAlphaOneMinusSrcAlpha,
  SrcAlphaOne
};

enum class ComparisonFunc : uint32
{
  Never = 0,
  Less,
  Equal,
  LessEqual,
  Greater,
  NotEqual,
  GreaterEqual,
  Always
};

struct PipelineDesc
{
  Shader* VertexShader = nullptr;
  Shader* FragmentShader = nullptr;
  bool BlendingEnable;
  BlendMode BlendMode;
  CullMode CullMode;
  bool DepthEnable;
  ComparisonFunc DepthFunc;
  VertexDecl VertexDecl;
};

class Pipeline
{
public:
  Pipeline(const PipelineDesc& desc) : m_Desc(desc) {}
  ~Pipeline() {}

  const PipelineDesc& GetDesc() const { return m_Desc; }
protected:
  PipelineDesc m_Desc;
};

enum class PixelFormat : uint32
{
  a8UnsignedNorm = 0,
  r8UnsignedNorm,
  r8SignedNorm,
  r8UnsignedInt,
  r8SignedInt,
  r16UnsignedNorm,
  r16SignedNorm,
  r16UnsignedInt,
  r16SignedInt,
  r16Float,
  r32UnsignedInt,
  r32SignedInt,
  r32Float,
  rg8UnsignedNorm,
  rg8SignedNorm,
  rg8UnsignedInt,
  rg8SignedInt,
  rgba8UnsignedNorm,
  rgba8UnsignedNormSRGB,
  rgba8SignedNorm,
  rgba8UnsignedInt,
  rgba8SignedInt,
  rgba16UnsignedNorm,
  rgba16SignedNorm,
  rgba16UnsignedInt,
  rgba16SignedInt,
  rgba16Float,
  rgba32UnsignedInt,
  rgba32SignedInt,
  rgba32Float,
  Depth,
  DepthStencil
};

enum class TextureWrap : uint32
{
  Repeat = 0,
  Clamp,
  MirroredRepeat,
  ClampToEdge,
  ClampToBorder
};

enum class TextureFilter : uint32
{
  Linear = 0,
  Nearest
};

class Texture
{
public:
  Texture(PixelFormat format, uint32 width, uint32 height, const void* data) : m_PixelFormat(format), m_Width(width), m_Height(height) {}
  ~Texture() {}
  
  virtual void SetMinFilter(TextureFilter filter) = 0;
  virtual void SetMagFilter(TextureFilter filter) = 0;
  virtual void SetWrapT(TextureWrap wrap) = 0;
  virtual void SetWrapS(TextureWrap wrap) = 0;
  virtual void SetWrapR(TextureWrap wrap) = 0;

  PixelFormat GetPixelFormat() const { return m_PixelFormat; }
  uint32 GetWidth() const { return m_Width; }
  uint32 GetHeight() const { return m_Height; }
protected:
  PixelFormat m_PixelFormat;
  uint32 m_Width;
  uint32 m_Height;
};

enum class PrimitiveType : uint32
{
  TriangleList = 0,
  LineList,
  PointList,
  TriangleStrip,
  LineStrip,
  TriangleFan
};

class RenderDevice
{
public:
  RenderDevice() {}
  ~RenderDevice() {}

  virtual void Clear(uint32 flags) = 0;
  virtual void ClearColor(const Vector4& color) = 0;
  virtual void SetVertexBuffer(Buffer* buffer) = 0;
  virtual void SetIndexBuffer(Buffer* buffer) = 0;
  virtual void SetUniformBuffer(Buffer* buffer, uint32 id) = 0;
  virtual void SetPipeline(Pipeline* pipeline) = 0;
  virtual void SetTexture(Texture* texture, uint32 slot) = 0;
  virtual void DrawArrays(PrimitiveType prim, uint32 offset, uint32 size) = 0;
  virtual void DrawIndexed(PrimitiveType prim, RHIFormat format, uint32 offset, uint32 size) = 0;
  virtual void SetViewport(int x, int y, int width, int height) = 0;

  virtual Buffer* CreateBuffer(BufferType type, const void* data, uint32 size, BufferFlags flags) = 0;
  virtual Shader* CreateShader(const char* source, ShaderType type) = 0;
  virtual Pipeline* CreatePipeline(const PipelineDesc& desc) = 0;
  virtual Texture* CreateTexture(PixelFormat format, uint32 width, uint32 height, const void* data) = 0;
public:
  static RenderDevice* Create_OpenGL(GraphicsContext* context);
  static RenderDevice* Create_None(GraphicsContext* context);
  static RenderDevice* Create(GraphicsContext* context);
};

inline
RenderDevice* RenderDevice::Create(GraphicsContext* context)
{
  switch (GraphicsAPI::Get())
  {
  case GraphicsAPIType::OpenGL: return RenderDevice::Create_OpenGL(context);
  case GraphicsAPIType::None: return RenderDevice::Create_None(context);
  }

  return nullptr;
}

ZK_NAMESPACE_END

#endif
