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
  Vertex
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

  virtual void SetData(const void* data, uint32 size) {}

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

struct PipelineDesc
{
  Shader* VertexShader = nullptr;
  Shader* FragmentShader = nullptr;
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

enum class PrimitiveType : uint32
{
  TriangleList,
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

  virtual void Clear(uint32 flags) {}
  virtual void ClearColor(const Vector4& color) {}
  virtual void SetVertexBuffer(Buffer* buffer) {}
  virtual void SetIndexBuffer(Buffer* buffer) {}
  virtual void SetPipeline(Pipeline* pipeline) {}
  virtual void DrawArrays(PrimitiveType prim, uint32 offset, uint32 size) {}
  virtual void DrawIndexed(PrimitiveType prim, RHIFormat format, uint32 offset, uint32 size) {}

  virtual Buffer* CreateBuffer(BufferType type, const void* data, uint32 size, BufferFlags flags) { return nullptr; }
  virtual Shader* CreateShader(const char* source, ShaderType type) { return nullptr; }
  virtual Pipeline* CreatePipeline(const PipelineDesc& desc) { return nullptr; }
};

RenderDevice* CreateRenderDevice_OpenGL(GraphicsContext* context);
RenderDevice* CreateRenderDevice_None(GraphicsContext* context);

inline
RenderDevice* CreateRenderDevice(GraphicsContext* context)
{
  switch (GraphicsAPI::Get())
  {
  case GraphicsAPIType::OpenGL: return CreateRenderDevice_OpenGL(context);
  case GraphicsAPIType::None: return CreateRenderDevice_None(context);
  }

  return nullptr;
}

ZK_NAMESPACE_END

#endif
