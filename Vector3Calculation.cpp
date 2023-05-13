#include "Vector3.h"


Vector3 Vec3Add(Vector3 add1, Vector3 add2) {
	Vector3 add3;
	add3.x = add1.x + add2.x;
	add3.y = add1.y + add2.y;
	add3.z = add1.z + add2.z;
	return add3;
}
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) { 
	Vector3 result{
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	};
	return result;
}


