#include "RHI_None.h"

ZK_NAMESPACE_BEGIN

GraphicsContext* GraphicsContext::Create_None()
{
  return new GraphicsContext_None();
}

RenderDevice* RenderDevice::Create_None(GraphicsContext* context)
{
  return new RenderDevice_None();
}

ZK_NAMESPACE_END
