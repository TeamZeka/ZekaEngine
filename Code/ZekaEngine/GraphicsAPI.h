#ifndef _H_GRAPHICS_API
#define _H_GRAPHICS_API

#include "HelperDefines.h"

ZK_NAMESPACE_BEGIN

enum class GraphicsAPIType : uint32
{
  None = 0,
  OpenGL
};

class GraphicsAPI
{
public:
  static void Set(GraphicsAPIType type);
  static GraphicsAPIType Get();
private:
  static GraphicsAPIType s_APIType;
};

ZK_NAMESPACE_END

#endif
