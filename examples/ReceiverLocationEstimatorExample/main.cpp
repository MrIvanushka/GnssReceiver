#include <fstream>
#include <iostream>

#include "../Math/Vector3.h"

using namespace gnssRecv::math;

Vector3 toGeocentric(const Vector3& vector)
{
    const double PI = 3.14159265358979323846;
    const double e = 0.006694379990141316996137335400448;
    const double a = 6378.137; // in km

    double d = sqrt(vector.x * vector.x + vector.y * vector.y);
    double b, l, h;

    if (d == 0)
    {
        b = PI * vector.z / (2 * abs(vector.z));
        h = vector.z * sin(b) - sqrt(1 - (e * sin(b)) * (e * sin(b)));

        return Vector3(b, 0, h);
    }

    double la = abs(asin(vector.y / d));

    if (vector.y < 0 && vector.x >= 0)
        l = 2 * PI - la;
    else if (vector.y < 0 && vector.x < 0)
        l = PI + la;
    else if (vector.y > 0 && vector.x < 0)
        l = PI - la;
    else if (vector.y > 0 && vector.x >= 0)
        l = la;
    else if (vector.y == 0 && vector.x > 0)
        l = 0;
    else //if (y == 0 && x < 0)
        l = PI;

    if (vector.z == 0)
    {
        return Vector3(0, l, d - a);
    }

    double r = vector.magnitude();
    double c = asin(vector.z / r);
    double p = (e * e * a) / (2 * r);
    double tolerance = 4.85e-10;
    double s1 = 0;
    double s2 = 0;
    unsigned it = 0;

    do
    {
        s1 = s2;
        b = c + s1;
        s2 = asin(p * sin(2 * b) / sqrt(1 - (e * sin(b)) * (e * sin(b))));
        it++;
    } while (abs(s1 - s2) > tolerance);

    std::cout << "iterations: " << it << std::endl;

    h = d * cos(b) + vector.z * sin(b) - a * sqrt(1 - (e * sin(b)) * (e * sin(b)));

    return Vector3(b, l, h);
}

int main()
{
    Vector3 vec(2'840.700, 2'181.300, 5'260.200);
    auto to = toGeocentric(vec);
    std::cout << to.x << " " << to.y << " " << to.z << std::endl;
    return 0;

}