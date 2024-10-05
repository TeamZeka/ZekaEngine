#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"

ZK_NAMESPACE_BEGIN

struct Quaternion
{
	float X;
	float Y;
	float Z;
	float W;

	Quaternion()
		: X(0.0f)
		, Y(0.0f)
		, Z(0.0f)
		, W(0.0f)
	{
	}

	Quaternion(const Quaternion& quat)
		: X(quat.X)
		, Y(quat.Y)
		, Z(quat.Z)
		, W(quat.W)
	{
	}

	Quaternion(float x, float y, float z, float w)
		: X(x)
		, Y(y)
		, Z(z)
		, W(w)
	{
	}

	Quaternion(const Vector4& vec)
		: X(vec.X)
		, Y(vec.Y)
		, Z(vec.Z)
		, W(vec.W)
	{
	}

	Quaternion(const Vector3& vec, float w)
		: X(vec.X)
		, Y(vec.Y)
		, Z(vec.Z)
		, W(w)
	{
	}

	Quaternion(const Vector2& vec, float z, float w)
		: X(vec.X)
		, Y(vec.Y)
		, Z(z)
		, W(w)
	{
	}

	Quaternion(float value)
		: X(value)
		, Y(value)
		, Z(value)
		, W(value)
	{
	}

	float Quaternion::GetAngle() const
	{
		const float len = Math::Square(X) + Math::Square(Y) + Math::Square(Z);
		if (Math::IsZero(len))
			return 0.0f;

		return 2.0f * acosf(Math::Clamp(W, -1.0f, 1.0f));
	}

	Vector3 GetAxis() const
	{
		const float len = Math::Square(X) + Math::Square(Y) + Math::Square(Z);
		if (Math::IsZero(len))
			return Vector3(1.0f, 0.0f, 0.0f);

		const float inv = 1.0f / sqrtf(len);
		return Vector3(X * inv, Y * inv, Z * inv);
	}

	Vector3 GetEuler() const
	{
		return Vector3(atan2f(2.0f * X * W - 2.0f * Y * Z, 1.0f - 2.0f * X * X - 2.0f * Z * Z),
			atan2f(2.0f * Y * W - 2 * X * Z, 1.0f - 2.0f * Y * Y - 2.0f * Z * Z),
			asinf(2.0f * X * Y + 2.0f * Z * W));
	}

	Quaternion operator+(const Quaternion& quat) const { return Quaternion(X + quat.X, Y + quat.Y, Z + quat.Z, W + quat.W); }
	Quaternion operator-(const Quaternion& quat) const { return Quaternion(X - quat.X, Y - quat.Y, Z - quat.Z, W - quat.W); }
	Quaternion operator*(float scalar) const { return Quaternion(X * scalar, Y * scalar, Z * scalar, W * scalar); }
	Quaternion operator-() const { return Quaternion(-X, -Y, -Z, -W); }
	Vector3 GetDirection(const Vector3& axis) const { return Rotate(axis); }
	Vector3 GetForwardDirection() const { return GetDirection(-Vector3::DirZ()); }
	Vector3 GetUpDirection() const { return GetDirection(Vector3::DirY()); }
	Vector3 GetRightDirection() const { return GetDirection(Vector3::DirX()); }
	Quaternion Quaternion::Conjugate() const { return Quaternion(-X, -Y, -Z, W); }

	static Vector3 GetDirection(const Quaternion& quat, const Vector3& axis) { return quat.GetDirection(axis); }
	static Vector3 Rotate(const Quaternion& quat, const Vector3& vec) { return quat.Rotate(vec); }
	static Vector3 GetForwardDirection(const Quaternion& quat) { return quat.GetForwardDirection(); }
	static Vector3 GetUpDirection(const Quaternion& quat) { return quat.GetUpDirection(); }
	static Vector3 GetRightDirection(const Quaternion& quat) { return quat.GetRightDirection(); }

	Quaternion operator*(const Quaternion& quat) const
	{
		Quaternion res;
		const float a = Y * quat.Z - Z * quat.Y;
		const float b = Z * quat.X - X * quat.Z;
		const float c = X * quat.Y - Y * quat.X;
		const float d = X * quat.X + Y * quat.Y + Z * quat.Z;
		res.X = X * quat.W + quat.X * W + a;
		res.Y = Y * quat.W + quat.Y * W + b;
		res.Z = Z * quat.W + quat.Z * W + c;
		res.W = W * quat.W - d;
		return res;
	}

	Quaternion& operator+=(const Quaternion& quat)
	{
		*this = *this + quat;
		return *this;
	}

	Quaternion& operator-=(const Quaternion& quat)
	{
		*this = *this - quat;
		return *this;
	}

	Quaternion& operator*=(const Quaternion& quat)
	{
		*this = *this * quat;
		return *this;
	}

	Quaternion& operator*=(float scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	static Quaternion Identity()
	{
		return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	}

	static Quaternion Euler(const Vector3& euler)
	{
		const float halfRoll = Math::Radians(euler.Z * 0.5f);
		const float halfPitch = Math::Radians(euler.X * 0.5f);
		const float halfYaw = Math::Radians(euler.Y * 0.5f);

		const float sinRollOver2 = sinf(halfRoll);
		const float cosRollOver2 = cosf(halfRoll);
		const float sinPitchOver2 = sinf(halfPitch);
		const float cosPitchOver2 = cosf(halfPitch);
		const float sinYawOver2 = sinf(halfYaw);
		const float cosYawOver2 = cosf(halfYaw);

		return Quaternion(
			cosYawOver2 * sinPitchOver2 * cosRollOver2 + sinYawOver2 * cosPitchOver2 * sinRollOver2,
			sinYawOver2 * cosPitchOver2 * cosRollOver2 - cosYawOver2 * sinPitchOver2 * sinRollOver2,
			cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2,
			cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2
		);
	}

	static Quaternion RotationYawPitchRoll(float yaw, float pitch, float roll)
	{
		const float halfRoll = roll * 0.5f;
		const float halfPitch = pitch * 0.5f;
		const float halfYaw = yaw * 0.5f;

		const float sinRollOver2 = sinf(halfRoll);
		const float cosRollOver2 = cosf(halfRoll);
		const float sinPitchOver2 = sinf(halfPitch);
		const float cosPitchOver2 = cosf(halfPitch);
		const float sinYawOver2 = sinf(halfYaw);
		const float cosYawOver2 = cosf(halfYaw);

		Quaternion res;
		res.W = cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2;
		res.X = cosYawOver2 * sinPitchOver2 * cosRollOver2 + sinYawOver2 * cosPitchOver2 * sinRollOver2;
		res.Y = sinYawOver2 * cosPitchOver2 * cosRollOver2 - cosYawOver2 * sinPitchOver2 * sinRollOver2;
		res.Z = cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2;
		return res;
	}

	static Quaternion RotationX(float a)
	{
		float angle = a * 0.5f;
		return Quaternion(sinf(angle), 0.0f, 0.0f, cosf(angle));
	}

	static Quaternion RotationY(float a)
	{
		float angle = a * 0.5f;
		return Quaternion(0.0f, sinf(angle), 0.0f, cosf(angle));
	}

	static Quaternion RotationZ(float a)
	{
		float angle = a * 0.5f;
		return Quaternion(0.0f, 0.0f, sinf(angle), cosf(angle));
	}

	Vector3 Rotate(const Vector3& vec) const
	{
		float x = (((W * vec.X) + (Y * vec.Z)) - (Z * vec.Y));
		float y = (((W * vec.Y) + (Z * vec.X)) - (X * vec.Z));
		float z = (((W * vec.Z) + (X * vec.Y)) - (Y * vec.X));
		float w = (((X * vec.X) + (Y * vec.Y)) + (Z * vec.Z));
		return Vector3(
			((((w * X) + (x * W)) - (y * Z)) + (z * Y)),
			((((w * Y) + (y * W)) - (z * X)) + (x * Z)),
			((((w * Z) + (z * W)) - (x * Y)) + (y * X))
		);
	}

	static float Norm(const Quaternion& quaternion)
	{
		float norm = 0.0f;
		norm = (quaternion.X * quaternion.X);
		norm = (norm + (quaternion.Y * quaternion.Y));
		norm = (norm + (quaternion.Z * quaternion.Z));
		norm = (norm + (quaternion.W * quaternion.W));
		return norm;
	}

	static Quaternion Normalize(const Quaternion& quat)
	{
		float norm = Norm(quat);
		float inv = 1.0f / sqrtf(norm);
		return quat * inv;
	}

	float& operator[](uint32_t idx) { return GetAddress()[idx]; }
	const float& operator[](uint32_t idx) const { return GetAddress()[idx]; }

	float* GetAddress() { return &X; }
	const float* GetAddress() const { return &X; }
};

ZK_NAMESPACE_END

#endif
