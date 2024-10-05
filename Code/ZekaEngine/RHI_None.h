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
};

class RenderDevice_None : public RenderDevice
{
public:
  RenderDevice_None() {}
  ~RenderDevice_None() {}

  void Clear(uint32 flags) override {}
  void ClearColor(const Vector4& color) override {}
};

ZK_NAMESPACE_END

#endif
