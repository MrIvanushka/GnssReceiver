#include "Vector3.h"

using namespace gnssRecv::math;

std::array<double, 3> Vector3::toArray() const
{
	std::array<double, 3> ret;

	ret[0] = x;
	ret[1] = y;
	ret[2] = z;

	return ret;
}

double Vector3::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::operator+(const Vector3& a)
{
	return Vector3(x + a.x, y + a.y, z + a.z);
}

Vector3 Vector3::operator - (const Vector3& a)
{
	return Vector3(x - a.x, y - a.y, z - a.z);
}