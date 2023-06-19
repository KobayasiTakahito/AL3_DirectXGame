#include "Vector3.h"
#include <math.h>

Vector3 Vec3Add(Vector3 add1, Vector3 add2) {
	Vector3 add3;
	add3.x = add1.x + add2.x;
	add3.y = add1.y + add2.y;
	add3.z = add1.z + add2.z;
	return add3;
}

Vector3 Vec3Sub(Vector3 sub1, Vector3 sub2) {
	Vector3 sub3;
	sub3.x = sub1.x - sub2.x;
	sub3.y = sub1.y - sub2.y;
	sub3.z = sub1.z - sub2.z;
	return sub3;
}

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) { 
	Vector3 result{
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	};
	return result;
}


Vector3 Vec3Normalize(Vector3& norm) { 
	float length = sqrtf((norm.x * norm.x) + (norm.y * norm.y) + (norm.z * norm.z)); 
	if (length > 0) {
		length = 1 / length;
	}
	Vector3 mag;
	mag.x = norm.x * length;
	mag.y = norm.y * length;
	mag.z = norm.z * length;
	return mag;
}
Vector3 Multiply(const Vector3& v1, const Vector3& v2) {
	return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}
Vector3 Multiply(float scalar, const Vector3& v) {
	return {v.x * scalar, v.y * scalar, v.z * scalar};
}