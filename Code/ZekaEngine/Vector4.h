#ifndef _H_VECTOR4
#define _H_VECTOR4

#include "Math.h"

ZK_NAMESPACE_BEGIN

struct Vector2;
struct Vector3;

struct Vector4
{
	float X;
	float Y;
	float Z;
	float W;

	Vector4(const Vector2& vec, float z, float w);
	Vector4(const Vector3& vec, float w);

	Vector4()
		: X(0.0f)
		, Y(0.0f)
		, Z(0.0f)
		, W(0.0f)
	{
	}

	Vector4(float x)
		: X(x)
		, Y(x)
		, Z(x)
		, W(x)
	{
	}

	Vector4(float x, float y, float z, float w)
		: X(x)
		, Y(y)
		, Z(z)
		, W(w)
	{
	}

	Vector4& operator+=(const Vector4& vec)
	{
		X += vec.X;
		Y += vec.Y;
		Z += vec.Z;
		W += vec.W;
		return *this;
	}

	Vector4& operator-=(const Vector4& vec)
	{
		X -= vec.X;
		Y -= vec.Y;
		Z -= vec.Z;
		W -= vec.W;
		return *this;
	}

	Vector4& operator*=(const Vector4& vec)
	{
		X *= vec.X;
		Y *= vec.Y;
		Z *= vec.Z;
		W *= vec.W;
		return *this;
	}

	Vector4& operator/=(const Vector4& vec)
	{
		X /= vec.X;
		Y /= vec.Y;
		Z /= vec.Z;
		W /= vec.W;
		return *this;
	}

	Vector4& operator+=(float x)
	{
		X += x;
		Y += x;
		Z += x;
		W += x;
		return *this;
	}

	Vector4& operator-=(float x)
	{
		X -= x;
		Y -= x;
		Z -= x;
		W -= x;
		return *this;
	}

	Vector4& operator*=(float x)
	{
		X *= x;
		Y *= x;
		Z *= x;
		W *= x;
		return *this;
	}

	Vector4& operator/=(float x)
	{
		X /= x;
		Y /= x;
		Z /= x;
		W /= x;
		return *this;
	}

	Vector4& operator=(const Vector4& vec)
	{
		X = vec.X;
		Y = vec.Y;
		Z = vec.Z;
		W = vec.W;
		return *this;
	}

	bool operator==(const Vector4& vec) const { return X == vec.X && Y == vec.Y && Z == vec.Z && W == vec.W; }
	bool operator!=(const Vector4& vec) const { return X != vec.X || Y != vec.Y || Z != vec.Z || W != vec.W; }
	bool operator>(const Vector4& vec) const { return X > vec.X && Y > vec.Y && Z > vec.Z && W > vec.W; }
	bool operator<(const Vector4& vec) const { return X < vec.X && Y < vec.Y && Z < vec.Z && W < vec.W; }
	bool operator>=(const Vector4& vec) const { return X >= vec.X && Y >= vec.Y && Z >= vec.Z && W >= vec.W; }
	bool operator<=(const Vector4& vec) const { return X <= vec.X && Y <= vec.Y && Z <= vec.Z && W <= vec.W; }
	Vector4 operator-() const { return Vector4(-X, -Y, -Z, -W); }
	Vector4 operator+(const Vector4& vec) const { return Vector4(X + vec.X, Y + vec.Y, Z + vec.Z, W + vec.W); }
	Vector4 operator-(const Vector4& vec) const { return Vector4(X - vec.X, Y - vec.Y, Z - vec.Z, W - vec.W); }
	Vector4 operator*(const Vector4& vec) const { return Vector4(X * vec.X, Y * vec.Y, Z * vec.Z, W * vec.W); }
	Vector4 operator/(const Vector4& vec) const { return Vector4(X / vec.X, Y / vec.Y, Z / vec.Z, W / vec.W); }
	Vector4 operator+(float x) const { return Vector4(X + x, Y + x, Z + x, W + x); }
	Vector4 operator-(float x) const { return Vector4(X - x, Y - x, Z - x, W - x); }
	Vector4 operator*(float x) const { return Vector4(X * x, Y * x, Z * x, W * x); }
	Vector4 operator/(float x) const { return Vector4(X / x, Y / x, Z / x, W / x); }
	float& operator[](uint32_t idx) { return GetAddress()[idx]; }
	const float& operator[](uint32_t idx) const { return GetAddress()[idx]; }

	static Vector4 DirX() { return Vector4(1.0f, 0.0f, 0.0f, 0.0f); }
	static Vector4 DirY() { return Vector4(0.0f, 1.0f, 0.0f, 0.0f); }
	static Vector4 DirZ() { return Vector4(0.0f, 0.0f, 1.0f, 0.0f); }
	static Vector4 DirW() { return Vector4(0.0f, 0.0f, 0.0f, 1.0f); }
	static Vector4 Normalize(const Vector4& vec)
	{
		float len = sqrtf(Math::Square(vec.X) + Math::Square(vec.Y) + Math::Square(vec.Z) + Math::Square(vec.W));
		return Vector4(vec.X / len, vec.Y / len, vec.Z / len, vec.W / len);
	}

	static float Dot(const Vector4& v0, const Vector4& v1)
	{
		Vector4 tmp = v0 * v1;
		return tmp.X + tmp.Y + tmp.Z + tmp.W;
	}

	static float Length(const Vector4& v)
	{
		return sqrtf(Dot(v, v));
	}

	static float Length2(const Vector4& v)
	{
		return Dot(v, v);
	}

	float* GetAddress() { return &X; }
	const float* GetAddress() const { return &X; }
};

inline Vector4 operator*(float v, const Vector4& vec) { return vec * v; }
inline Vector4 operator+(float v, const Vector4& vec) { return vec + v; }
inline Vector4 operator/(float v, const Vector4& vec) { return vec / v; }
inline Vector4 operator-(float v, const Vector4& vec) { return vec - v; }

ZK_NAMESPACE_END

#endif
