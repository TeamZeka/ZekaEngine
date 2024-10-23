#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

ZK_NAMESPACE_BEGIN

Vector4::Vector4(const Vector2& vec, float z, float w)
  : X(vec.X)
  , Y(vec.Y)
  , Z(z)
  , W(w)
{
}

Vector4::Vector4(const Vector3& vec, float w)
  : X(vec.X)
  , Y(vec.Y)
  , Z(vec.Z)
  , W(w)
{
}

ZK_NAMESPACE_END
