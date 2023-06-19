#pragma once
#include "Matrix4x4.h"
/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;
};

// Vec３の加算

Vector3 Vec3Add(Vector3 add1, Vector3 add2);
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
Vector3 Vec3Sub(Vector3 sub1, Vector3 sub2);
Vector3 Vec3Normalize(Vector3& norm);
Vector3 Multiply(const Vector3& v1, const Vector3& v2);
Vector3 Multiply(float scalar, const Vector3& v);