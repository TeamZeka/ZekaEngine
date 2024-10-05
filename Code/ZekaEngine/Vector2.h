#ifndef _H_VECTOR2
#define _H_VECTOR2

#include "Math.h"

ZK_NAMESPACE_BEGIN

struct Vector3;
struct Vector4;

struct Vector2
{
	float X;
	float Y;
	
	Vector2(const Vector3& vec);
	Vector2(const Vector4& vec);

	Vector2()
		: X(0.0f)
		, Y(0.0f)
	{
	}

	Vector2(float x)
		: X(x)
		, Y(x)
	{
	}

	Vector2(float x, float y)
		: X(x)
		, Y(y)
	{
	}

	Vector2& operator+=(const Vector2& vec)
	{
		X += vec.X;
		Y += vec.Y;
		return *this;
	}

	Vector2& operator-=(const Vector2& vec)
	{
		X -= vec.X;
		Y -= vec.Y;
		return *this;
	}

	Vector2& operator*=(const Vector2& vec)
	{
		X *= vec.X;
		Y *= vec.Y;
		return *this;
	}

	Vector2& operator/=(const Vector2& vec)
	{
		X /= vec.X;
		Y /= vec.Y;
		return *this;
	}

	Vector2& operator+=(float x)
	{
		X += x;
		Y += x;
		return *this;
	}

	Vector2& operator-=(float x)
	{
		X -= x;
		Y -= x;
		return *this;
	}

	Vector2& operator*=(float x)
	{
		X *= x;
		Y *= x;
		return *this;
	}

	Vector2& operator/=(float x)
	{
		X /= x;
		Y /= x;
		return *this;
	}

	Vector2& operator=(const Vector2& vec)
	{
		X = vec.X;
		Y = vec.Y;
		return *this;
	}

	bool operator==(const Vector2& vec) const { return X == vec.X && Y == vec.Y; }
	bool operator!=(const Vector2& vec) const { return X != vec.X || Y != vec.Y; }
	bool operator>(const Vector2& vec) const { return X > vec.X && Y > vec.Y; }
	bool operator<(const Vector2& vec) const { return X < vec.X && Y < vec.Y; }
	bool operator>=(const Vector2& vec) const { return X >= vec.X && Y >= vec.Y; }
	bool operator<=(const Vector2& vec) const { return X <= vec.X && Y <= vec.Y; }
	Vector2 operator-() const { return Vector2(-X, -Y); }
	Vector2 operator+(const Vector2& vec) const { return Vector2(X + vec.X, Y + vec.Y); }
	Vector2 operator-(const Vector2& vec) const { return Vector2(X - vec.X, Y - vec.Y); }
	Vector2 operator*(const Vector2& vec) const { return Vector2(X * vec.X, Y * vec.Y); }
	Vector2 operator/(const Vector2& vec) const { return Vector2(X / vec.X, Y / vec.Y); }
	Vector2 operator+(float x) const { return Vector2(X + x, Y + x); }
	Vector2 operator-(float x) const { return Vector2(X - x, Y - x); }
	Vector2 operator*(float x) const { return Vector2(X * x, Y * x); }
	Vector2 operator/(float x) const { return Vector2(X / x, Y / x); }
	float& operator[](uint32_t idx) { return GetAddress()[idx]; }
	const float& operator[](uint32_t idx) const { return GetAddress()[idx]; }

	static Vector2 DirX() { return Vector2(1.0f, 0.0f); }
	static Vector2 DirY() { return Vector2(0.0f, 1.0f); }
	static Vector2 Normalize(const Vector2& vec)
	{
		float len = sqrtf(Math::Square(vec.X) + Math::Square(vec.Y));
		return Vector2(vec.X / len, vec.Y / len);
	}

	static float Dot(const Vector2& v0, const Vector2& v1)
	{
		Vector2 tmp = v0 * v1;
		return tmp.X + tmp.Y;
	}

	static float Length(const Vector2& v)
	{
		return sqrtf(Dot(v, v));
	}

	static float Length2(const Vector2& v)
	{
		return Dot(v, v);
	}

	float* GetAddress() { return &X; }
	const float* GetAddress() const { return &X; }
};

inline Vector2 operator*(float v, const Vector2& vec) { return vec * v; }
inline Vector2 operator+(float v, const Vector2& vec) { return vec + v; }
inline Vector2 operator/(float v, const Vector2& vec) { return vec / v; }
inline Vector2 operator-(float v, const Vector2& vec) { return vec - v; }

ZK_NAMESPACE_END

#endif
