#ifndef _H_TRANSFORM
#define _H_TRANSFORM

#include "Quaternion.h"
#include "Matrix4.h"

ZK_NAMESPACE_BEGIN

struct Transform
{
	Vector3 Position;
	Quaternion Orientation;
	Vector3 Scale;

	Transform()
		: Position(0.0f)
		, Orientation(0.0f, 0.0f, 0.0f, 1.0f)
		, Scale(1.0f)
	{
	}

	Transform(const Vector3& pos)
		: Position(pos)
		, Orientation(0.0f, 0.0f, 0.0f, 1.0f)
		, Scale(1.0f)
	{
	}

	Transform(const Vector3& pos, const Quaternion& orientation, const Vector3& scale)
		: Position(pos)
		, Orientation(orientation)
		, Scale(scale)
	{
	}

	Matrix4 GetWorldMatrix() const { return Matrix4::Translate(Position) * Matrix4::Rotate(Orientation) * Matrix4::Scale(Scale); }
	Vector3 GetDirection(const Vector3& axis) const { return Orientation.GetDirection(axis); }
	Vector3 GetRight() const { return GetDirection(Vector3::DirX()); }
	Vector3 GetLeft() const { return GetDirection(-Vector3::DirX()); }
	Vector3 GetUp() const { return GetDirection(Vector3::DirY()); }
	Vector3 GetDown() const { return GetDirection(-Vector3::DirY()); }
	Vector3 GetForward() const { return GetDirection(-Vector3::DirZ()); }
	Vector3 GetBackward() const { return GetDirection(Vector3::DirZ()); }
};

ZK_NAMESPACE_END

#endif
