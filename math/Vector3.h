#pragma once

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
