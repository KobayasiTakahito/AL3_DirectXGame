#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cassert>
#include <cmath>

// Matrix4x4 積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
// Matrix4x4 引き算
Matrix4x4 Sub(const Matrix4x4& m1, const Matrix4x4& m2);
    // 並行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

Matrix4x4 MakeScaleMatrix(const Vector3& scale);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

// 軸周りの回転行列
Matrix4x4 MakeRotateZMatrix(float radion);

Matrix4x4 MakeRotateXMatrix(float radion);

Matrix4x4 MakeRotateYMatrix(float radion);
// アフィン変換
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Matrix4x4 Inverse(const Matrix4x4& m);

float Dot(const Vector3& v1, const Vector3& v2);
float Length(const Vector3& v);
Vector3 Normalise(const Vector3& v);
Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth);
