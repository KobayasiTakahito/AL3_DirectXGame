#include "Vector3.h"


Vector3 Vec3Add(Vector3 add1, Vector3 add2) {
	Vector3 add3;
	add3.x = add1.x + add2.x;
	add3.y = add1.y + add2.y;
	add3.z = add1.z + add2.z;
	return add3;
}
