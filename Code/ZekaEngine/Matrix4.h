#ifndef _H_MATRIX4
#define _H_MATRIX4

#include "Quaternion.h"
#include "Vector4.h"
#include "Math.h"

ZK_NAMESPACE_BEGIN

struct Matrix4
{
  Vector4 Columns[4];

  Matrix4()
  {
  }

  Matrix4(const Vector4& c0, const Vector4& c1, const Vector4& c2, const Vector4& c3)
  {
    Columns[0] = c0;
    Columns[1] = c1;
    Columns[2] = c2;
    Columns[3] = c3;
  }

  Matrix4(float diagonal)
  {
    Columns[0][0] = diagonal;
    Columns[1][1] = diagonal;
    Columns[2][2] = diagonal;
    Columns[3][3] = diagonal;
  }

  bool operator==(const Matrix4& mat) const
  {
    return Columns[0] == mat[0] &&
      Columns[1] == mat[1] &&
      Columns[2] == mat[2] &&
      Columns[3] == mat[3];
  }

  bool operator!=(const Matrix4& mat) const
  {
    return Columns[0] != mat[0] ||
      Columns[1] != mat[1] ||
      Columns[2] != mat[2] ||
      Columns[3] != mat[3];
  }

  Matrix4 operator+(const Matrix4& mat) const
  {
    Matrix4 res;
    res[0] = Columns[0] + mat[0];
    res[1] = Columns[1] + mat[1];
    res[2] = Columns[2] + mat[2];
    res[3] = Columns[3] + mat[3];
    return res;
  }

  Matrix4 operator-(const Matrix4& mat) const
  {
    Matrix4 res;
    res[0] = Columns[0] - mat[0];
    res[1] = Columns[1] - mat[1];
    res[2] = Columns[2] - mat[2];
    res[3] = Columns[3] - mat[3];
    return res;
  }

  Matrix4 operator*(const Matrix4& mat) const
  {
    Vector4 sA0 = Columns[0];
    Vector4 sA1 = Columns[1];
    Vector4 sA2 = Columns[2];
    Vector4 sA3 = Columns[3];

    Vector4 sB0 = mat[0];
    Vector4 sB1 = mat[1];
    Vector4 sB2 = mat[2];
    Vector4 sB3 = mat[3];

    Matrix4 res;
    res[0] = sA0 * sB0[0] + sA1 * sB0[1] + sA2 * sB0[2] + sA3 * sB0[3];
    res[1] = sA0 * sB1[0] + sA1 * sB1[1] + sA2 * sB1[2] + sA3 * sB1[3];
    res[2] = sA0 * sB2[0] + sA1 * sB2[1] + sA2 * sB2[2] + sA3 * sB2[3];
    res[3] = sA0 * sB3[0] + sA1 * sB3[1] + sA2 * sB3[2] + sA3 * sB3[3];
    return res;
  }

  Matrix4 operator/(const Matrix4& mat) const
  {
    Matrix4 res;
    res[0] = Columns[0] / mat[0];
    res[1] = Columns[1] / mat[1];
    res[2] = Columns[2] / mat[2];
    res[3] = Columns[3] / mat[3];
    return res;
  }

  Matrix4 operator*(float value) const
  {
    Matrix4 res;
    res[0] = Columns[0] * value;
    res[1] = Columns[1] * value;
    res[2] = Columns[2] * value;
    res[3] = Columns[3] * value;
    return res;
  }

  Matrix4 operator/(float value) const
  {
    Matrix4 res;
    const float inv = 1.0f / value;
    res[0] = Columns[0] * inv;
    res[1] = Columns[1] * inv;
    res[2] = Columns[2] * inv;
    res[3] = Columns[3] * inv;
    return res;
  }

  Matrix4& operator*=(const Matrix4& mat)
  {
    *this = *this * mat;
    return *this;
  }

  Matrix4& operator/=(const Matrix4& mat)
  {
    *this = *this / mat;
    return *this;
  }

  Matrix4& operator+=(const Matrix4& mat)
  {
    *this = *this + mat;
    return *this;
  }

  Matrix4& operator-=(const Matrix4& mat)
  {
    *this = *this - mat;
    return *this;
  }

  Matrix4& operator*=(float v)
  {
    *this = *this * v;
    return *this;
  }

  Matrix4& operator/=(float v)
  {
    *this = *this / v;
    return *this;
  }

  Matrix4& operator+=(float v)
  {
    *this = *this + v;
    return *this;
  }

  Matrix4& operator-=(float v)
  {
    *this = *this - v;
    return *this;
  }

  static Matrix4 Identity()
  {
    return Matrix4(1.0f);
  }

  static Matrix4 Perspective(float fov, float aspectRatio, float zNear, float zFar)
  {
    float tanHalfFovy = tanf(fov * 0.5f);

    Matrix4 res;
    res[0][0] = 1.0f / (aspectRatio * tanHalfFovy);
    res[1][1] = 1.0f / (tanHalfFovy);
    res[2][2] = -(zFar + zNear) / (zFar - zNear);
    res[2][3] = -1.0f;
    res[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
    return res;
  }

  static Matrix4 Orthographic(float left, float right, float bottom, float top, float zNear, float zFar)
  {
    Matrix4 res(1.0f);
    res[0][0] = 2.0f / (right - left);
    res[1][1] = 2.0f / (top - bottom);
    res[2][2] = 2.0f / (zNear - zFar);
    res[3][0] = (left + right) / (left - right);
    res[3][1] = (bottom + top) / (bottom - top);
    res[3][2] = (zFar + zNear) / (zFar - zNear);
    return res;
  }

  static Matrix4 Translate(const Vector3& position)
  {
    Matrix4 res(1.0f);
    res[3][0] = position.X;
    res[3][1] = position.Y;
    res[3][2] = position.Z;
    return res;
  }

  static Matrix4 Scale(const Vector3& scale)
  {
    Matrix4 res(1.0f);
    res[0][0] = scale.X;
    res[1][1] = scale.Y;
    res[2][2] = scale.Z;
    return res;
  }

  static Matrix4 RotateX(float angle)
  {
    float c = cosf(angle);
    float s = sinf(angle);

    Matrix4 res(1.0f);
    res[1][1] = c;
    res[2][2] = c;
    res[2][1] = -s;
    res[1][2] = s;
    return res;
  }

  static Matrix4 RotateY(float angle)
  {
    float c = cosf(angle);
    float s = sinf(angle);

    Matrix4 res(1.0f);
    res[0][0] = c;
    res[2][2] = c;
    res[0][2] = -s;
    res[2][0] = s;
    return res;
  }

  static Matrix4 RotateZ(float angle)
  {
    float c = cosf(angle);
    float s = sinf(angle);

    Matrix4 res(1.0f);
    res[0][0] = c;
    res[1][1] = c;
    res[0][1] = s;
    res[1][0] = -s;
    return res;
  }

  static Matrix4 Inverse(const Matrix4& mat)
  {
    float c00 = mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3];
    float c02 = mat[1][2] * mat[3][3] - mat[3][2] * mat[1][3];
    float c03 = mat[1][2] * mat[2][3] - mat[2][2] * mat[1][3];

    float c04 = mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3];
    float c06 = mat[1][1] * mat[3][3] - mat[3][1] * mat[1][3];
    float c07 = mat[1][1] * mat[2][3] - mat[2][1] * mat[1][3];

    float c08 = mat[2][1] * mat[3][2] - mat[3][1] * mat[2][2];
    float c10 = mat[1][1] * mat[3][2] - mat[3][1] * mat[1][2];
    float c11 = mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2];

    float c12 = mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3];
    float c14 = mat[1][0] * mat[3][3] - mat[3][0] * mat[1][3];
    float c15 = mat[1][0] * mat[2][3] - mat[2][0] * mat[1][3];

    float c16 = mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2];
    float c18 = mat[1][0] * mat[3][2] - mat[3][0] * mat[1][2];
    float c19 = mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2];

    float c20 = mat[2][0] * mat[3][1] - mat[3][0] * mat[2][1];
    float c22 = mat[1][0] * mat[3][1] - mat[3][0] * mat[1][1];
    float c23 = mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1];

    Vector4 f0(c00, c00, c02, c03);
    Vector4 f1(c04, c04, c06, c07);
    Vector4 f2(c08, c08, c10, c11);
    Vector4 f3(c12, c12, c14, c15);
    Vector4 f4(c16, c16, c18, c19);
    Vector4 f5(c20, c20, c22, c23);

    Vector4 v0(mat[1][0], mat[0][0], mat[0][0], mat[0][0]);
    Vector4 v1(mat[1][1], mat[0][1], mat[0][1], mat[0][1]);
    Vector4 v2(mat[1][2], mat[0][2], mat[0][2], mat[0][2]);
    Vector4 v3(mat[1][3], mat[0][3], mat[0][3], mat[0][3]);

    Vector4 inv0(v1 * f0 - v2 * f1 + v3 * f2);
    Vector4 inv1(v0 * f0 - v2 * f3 + v3 * f4);
    Vector4 inv2(v0 * f1 - v1 * f3 + v3 * f5);
    Vector4 inv3(v0 * f2 - v1 * f4 + v2 * f5);

    Vector4 sA(+1, -1, +1, -1);
    Vector4 sB(-1, +1, -1, +1);
    Matrix4 inv(inv0 * sA, inv1 * sB, inv2 * sA, inv3 * sB);

    Vector4 r0(inv[0][0], inv[1][0], inv[2][0], inv[3][0]);

    Vector4 d0(mat[0] * r0);
    float d1 = (d0.X + d0.Y) + (d0.Z + d0.W);

    float determinant = 1.0f / d1;

    return inv * determinant;
  }

  static Matrix4 Rotate(const Quaternion& rotation)
  {
    const float xx = rotation.X * rotation.X;
    const float yy = rotation.Y * rotation.Y;
    const float zz = rotation.Z * rotation.Z;
    const float xy = rotation.X * rotation.Y;
    const float zw = rotation.Z * rotation.W;
    const float zx = rotation.Z * rotation.X;
    const float yw = rotation.Y * rotation.W;
    const float yz = rotation.Y * rotation.Z;
    const float xw = rotation.X * rotation.W;

    Matrix4 res(1.0f);
    res[0][0] = 1.0f - 2.0f * (yy + zz);
    res[0][1] = 2.0f * (xy + zw);
    res[0][2] = 2.0f * (zx - yw);
    res[0][3] = 0;

    res[1][0] = 2.0f * (xy - zw);
    res[1][1] = 1.0f - 2.0f * (zz + xx);
    res[1][2] = 2.0f * (yz + xw);
    res[1][3] = 0;

    res[2][0] = 2.0f * (zx + yw);
    res[2][1] = 2.0f * (yz - xw);
    res[2][2] = 1.0f - 2.0f * (yy + xx);
    res[2][3] = 0.0f;

    res[3][0] = 0.0f;
    res[3][1] = 0.0f;
    res[3][2] = 0.0f;
    res[3][3] = 1.0f;
    return res;
  }

  Vector4 operator*(const Vector4& vec) const
  {
    Vector4 Mov0(vec[0]);
    Vector4 Mov1(vec[1]);
    Vector4 Mul0 = Columns[0] * Mov0;
    Vector4 Mul1 = Columns[1] * Mov1;
    Vector4 Add0 = Mul0 + Mul1;
    Vector4 Mov2(vec[2]);
    Vector4 Mov3(vec[3]);
    Vector4 Mul2 = Columns[2] * Mov2;
    Vector4 Mul3 = Columns[3] * Mov3;
    Vector4 Add1 = Mul2 + Mul3;
    Vector4 Add2 = Add0 + Add1;
    return Add2;
  }

  Vector4& operator[](uint32_t idx) { return Columns[idx]; }
  const Vector4& operator[](uint32_t idx) const { return Columns[idx]; }

  float* GetAddress() { return &Columns[0][0]; }
  const float* GetAddress() const { return &Columns[0][0]; };
};

inline Matrix4 operator*(float v, const Matrix4& vec) { return vec * v; }
inline Matrix4 operator+(float v, const Matrix4& vec) { return vec + v; }
inline Matrix4 operator/(float v, const Matrix4& vec) { return vec / v; }
inline Matrix4 operator-(float v, const Matrix4& vec) { return vec - v; }

ZK_NAMESPACE_END

#endif
