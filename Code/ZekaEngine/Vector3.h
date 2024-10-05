#ifndef _H_VECTOR3
#define _H_VECTOR3

#include "Math.h"

ZK_NAMESPACE_BEGIN

struct Vector2;
struct Vector4;

struct Vector3
{
	float X;
	float Y;
	float Z;
	
	Vector3(const Vector2& vec, float z);
	Vector3(const Vector4& vec);

	Vector3()
		: X(0.0f)
		, Y(0.0f)
		, Z(0.0f)
	{
	}

	Vector3(float x)
		: X(x)
		, Y(x)
		, Z(x)
	{
	}

	Vector3(float x, float y, float z)
		: X(x)
		, Y(y)
		, Z(z)
	{
	}

	Vector3& operator+=(const Vector3& vec)
	{
		X += vec.X;
		Y += vec.Y;
		Z += vec.Z;
		return *this;
	}

	Vector3& operator-=(const Vector3& vec)
	{
		X -= vec.X;
		Y -= vec.Y;
		Z -= vec.Z;
		return *this;
	}

	Vector3& operator*=(const Vector3& vec)
	{
		X *= vec.X;
		Y *= vec.Y;
		Z *= vec.Z;
		return *this;
	}

	Vector3& operator/=(const Vector3& vec)
	{
		X /= vec.X;
		Y /= vec.Y;
		Z /= vec.Z;
		return *this;
	}

	Vector3& operator+=(float x)
	{
		X += x;
		Y += x;
		Z += x;
		return *this;
	}

	Vector3& operator-=(float x)
	{
		X -= x;
		Y -= x;
		Z -= x;
		return *this;
	}

	Vector3& operator*=(float x)
	{
		X *= x;
		Y *= x;
		Z *= x;
		return *this;
	}

	Vector3& operator/=(float x)
	{
		X /= x;
		Y /= x;
		Z /= x;
		return *this;
	}

	Vector3& operator=(const Vector3& vec)
	{
		X = vec.X;
		Y = vec.Y;
		Z = vec.Z;
		return *this;
	}

	bool operator==(const Vector3& vec) const { return X == vec.X && Y == vec.Y && Z == vec.Z; }
	bool operator!=(const Vector3& vec) const { return X != vec.X || Y != vec.Y || Z != vec.Z; }
	bool operator>(const Vector3& vec) const { return X > vec.X && Y > vec.Y && Z > vec.Z; }
	bool operator<(const Vector3& vec) const { return X < vec.X && Y < vec.Y && Z < vec.Z; }
	bool operator>=(const Vector3& vec) const { return X >= vec.X && Y >= vec.Y && Z >= vec.Z; }
	bool operator<=(const Vector3& vec) const { return X <= vec.X && Y <= vec.Y && Z <= vec.Z; }
	Vector3 operator-() const { return Vector3(-X, -Y, -Z); }
	Vector3 operator+(const Vector3& vec) const { return Vector3(X + vec.X, Y + vec.Y, Z + vec.Z); }
	Vector3 operator-(const Vector3& vec) const { return Vector3(X - vec.X, Y - vec.Y, Z - vec.Z); }
	Vector3 operator*(const Vector3& vec) const { return Vector3(X * vec.X, Y * vec.Y, Z * vec.Z); }
	Vector3 operator/(const Vector3& vec) const { return Vector3(X / vec.X, Y / vec.Y, Z / vec.Z); }
	Vector3 operator+(float x) const { return Vector3(X + x, Y + x, Z + x); }
	Vector3 operator-(float x) const { return Vector3(X - x, Y - x, Z - x); }
	Vector3 operator*(float x) const { return Vector3(X * x, Y * x, Z * x); }
	Vector3 operator/(float x) const { return Vector3(X / x, Y / x, Z / x); }
	float& operator[](uint32_t idx) { return GetAddress()[idx]; }
	const float& operator[](uint32_t idx) const { return GetAddress()[idx]; }
	
	static Vector3 DirX() { return Vector3(1.0f, 0.0f, 0.0f); }
	static Vector3 DirY() { return Vector3(0.0f, 1.0f, 0.0f); }
	static Vector3 DirZ() { return Vector3(0.0f, 0.0f, 1.0f); }
	static Vector3 Normalize(const Vector3& vec)
	{
		float len = sqrtf(Math::Square(vec.X) + Math::Square(vec.Y) + Math::Square(vec.Z));
		return Vector3(vec.X / len, vec.Y / len, vec.Z / len);
	}

	static float Dot(const Vector3& v0, const Vector3& v1)
	{
		Vector3 tmp = v0 * v1;
		return tmp.X + tmp.Y + tmp.Z;
	}

	static float Length(const Vector3& v)
	{
		return sqrtf(Dot(v, v));
	}

	static float Length2(const Vector3& v)
	{
		return Dot(v, v);
	}

	static Vector3 Cross(const Vector3& x, const Vector3& y)
	{
		return Vector3(
			x.Y * y.Z - y.Y * x.Z,
			x.Z * y.X - y.Z * x.X,
			x.X * y.Y - y.X * x.Y
		);
	}

	float* GetAddress() { return &X; }
	const float* GetAddress() const { return &X; }
};

inline Vector3 operator*(float v, const Vector3& vec) { return vec * v; }
inline Vector3 operator+(float v, const Vector3& vec) { return vec + v; }
inline Vector3 operator/(float v, const Vector3& vec) { return vec / v; }
inline Vector3 operator-(float v, const Vector3& vec) { return vec - v; }

ZK_NAMESPACE_END

#endif
