#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

ZK_NAMESPACE_BEGIN

Vector3::Vector3(const Vector2& vec, float z)
  : X(vec.X)
  , Y(vec.Y)
  , Z(z)
{
}

Vector3::Vector3(const Vector4& vec)
  : X(vec.X)
  , Y(vec.Y)
  , Z(vec.Z)
{
}

ZK_NAMESPACE_END
