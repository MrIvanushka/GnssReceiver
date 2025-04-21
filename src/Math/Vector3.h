#pragma once

#include <array>
#include <iomanip>
#include <iostream>

namespace gnssRecv
{
namespace math
{

struct Vector3
{
public:
	Vector3() = default;

	Vector3(const std::array<double, 3>& arr) : x(arr[0]), y(arr[1]), z(arr[2]) {}

	Vector3(double X, double Y, double Z) : x(X), y(Y), z(Z) {}

	std::array<double, 3> toArray() const;

	double magnitude() const;

	Vector3 operator+(const Vector3&);

	Vector3 operator-(const Vector3&);

	double x;
	double y;
	double z;
};

} //namespace math

} //namespace gnssRecv