#include "GraphicsAPI.h"

ZK_NAMESPACE_BEGIN

GraphicsAPIType GraphicsAPI::s_APIType = GraphicsAPIType::None;

void GraphicsAPI::Set(GraphicsAPIType type)
{
  s_APIType = type;
}

GraphicsAPIType GraphicsAPI::Get()
{
  return s_APIType;
}

ZK_NAMESPACE_END
