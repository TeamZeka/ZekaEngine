#ifndef _H_RHI_NONE
#define _H_RHI_NONE

#include "GraphicsContext.h"
#include "RHIBase.h"

ZK_NAMESPACE_BEGIN

class GraphicsContext_None : public GraphicsContext
{
public:
  GraphicsContext_None() {}
  ~GraphicsContext_None() {}

  bool InitializeGraphics(void* windowHandle) override 
  { 
    m_WindowHandle = windowHandle; 
    
    return true;
  }
  
  void ShutdownGraphics() override {}
  void Present() override {}
  void SetVSync(bool vsync) override { m_IsVSync = vsync; }
};

class Buffer_None : public Buffer
{
public:
  Buffer_None(BufferType type, const void* data, uint32 size, BufferFlags flags) : Buffer(type, data, size, flags) {}
  ~Buffer_None() {}

  void SetData(const void* data, uint32 size) override {}
};

class Shader_None : public Shader
{
public:
  Shader_None(const char* source, ShaderType type) : Shader(source, type) {}
  ~Shader_None() {}
};

class Pipeline_None : public Pipeline
{
public:
  Pipeline_None(const PipelineDesc& desc) : Pipeline(desc) {}
  ~Pipeline_None() {}
};

class Texture_None : public Texture
{
public:
  Texture_None(PixelFormat format, uint32 width, uint32 height, const void* data) : Texture(format, width, height, data) {}
  ~Texture_None() {}

  void SetMinFilter(TextureFilter filter) override {}
  void SetMagFilter(TextureFilter filter) override {}
  void SetWrapT(TextureWrap wrap) override {}
  void SetWrapS(TextureWrap wrap) override {}
  void SetWrapR(TextureWrap wrap) override {}
};

class RenderDevice_None : public RenderDevice
{
public:
  RenderDevice_None() {}
  ~RenderDevice_None() {}

  void Clear(uint32 flags) override {}
  void ClearColor(const Vector4& color) override {}
  void SetVertexBuffer(Buffer* buffer) override {}
  void SetIndexBuffer(Buffer* buffer) override {}
  void SetUniformBuffer(Buffer* buffer, uint32 id) override {}
  void SetPipeline(Pipeline* pipeline) override {}
  void SetTexture(Texture* texture, uint32 slot) override {}
  void DrawArrays(PrimitiveType prim, uint32 offset, uint32 size) override {}
  void DrawIndexed(PrimitiveType prim, RHIFormat format, uint32 offset, uint32 size) override {}
  void SetViewport(int x, int y, int width, int height) override {}

  Buffer* CreateBuffer(BufferType type, const void* data, uint32 size, BufferFlags flags) override { return new Buffer_None(type, data, size, flags); }
  Shader* CreateShader(const char* source, ShaderType type) override { return new Shader_None(source, type); }
  Pipeline* CreatePipeline(const PipelineDesc& desc) override { return new Pipeline_None(desc); }
  Texture* CreateTexture(PixelFormat format, uint32 width, uint32 height, const void* data) override { return new Texture_None(format, width, height, data); }
};

ZK_NAMESPACE_END

#endif
