#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

ZK_NAMESPACE_BEGIN

Vector2::Vector2(const Vector3& vec)
  : X(vec.X)
  , Y(vec.Y)
{
}

Vector2::Vector2(const Vector4& vec)
  : X(vec.X)
  , Y(vec.Y)
{
}

ZK_NAMESPACE_END
