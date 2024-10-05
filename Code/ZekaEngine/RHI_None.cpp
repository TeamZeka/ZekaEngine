#include "RHI_None.h"

ZK_NAMESPACE_BEGIN

GraphicsContext* CreateGraphicsContext_None()
{
  return new GraphicsContext_None();
}

RenderDevice* CreateRenderDevice_None(GraphicsContext* context)
{
  return new RenderDevice_None();
}

ZK_NAMESPACE_END