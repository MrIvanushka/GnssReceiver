#include "GlonassSatLocationEstimator.h"

using namespace gnssRecv::satLocationEstimator;
using gnssRecv::math::Vector3;

GlonassSatLocationEstimator::GlonassSatLocationEstimator(
	std::shared_ptr<IGlonassEphemerisStorage> storage) :
	_storage(storage)
{}

Vector3 GlonassSatLocationEstimator::calculateLocation(double currentTime)
{
	auto locationAndVelocity = _storage->locationAndVelocity();
	currentTime = ephimeridicTime(currentTime);
	estimateRungeKutta(locationAndVelocity, _storage->acceleration(), currentTime - _storage->timestamp());
	_storage->updateLocationAndVelocity(locationAndVelocity, currentTime);

	return toGeocentric(Vector3(locationAndVelocity[0], locationAndVelocity[1], locationAndVelocity[2]));
}

void GlonassSatLocationEstimator::estimateRungeKutta(
	std::array<double, 6>& y,
	const std::array<double, 3>& acceleration,
	double deltaTime) const
{
	std::array<double, 6> K;
	std::array<double, 6> dy;
	std::array<double, 6> y_mod;

	auto iterativeTime = 0.0;
	auto iterativeTimestep = 0.001;
	for (auto currentIter = 1u; iterativeTime < deltaTime; currentIter++)
	{
		unsigned stepsCount = 4;

		for (auto i = 0u; i < stepsCount; i++)
		{
			std::array<double, 6> arr;

			if (i == 0)
				arr = estimateDiff(y, acceleration);
			else
				arr = estimateDiff(y_mod, acceleration);

			for (auto j = 0u; j < 6; j++)
			{
				K[j] = iterativeTimestep * arr[j];

				if (i == 0)
					dy[j] = K[j];
				else if (i == stepsCount - 1)
					dy[j] += K[j];
				else
					dy[j] += K[j] * 2;

				y_mod[j] = y[j] + dy[j] / 2;
			}
		}

		for (auto i = 0u; i < 6; i++)
		{
			y[i] += dy[i] / 6.0;
		}
		iterativeTime += iterativeTimestep;

		if ((iterativeTime + iterativeTimestep) > deltaTime)
		{
			iterativeTimestep = deltaTime - iterativeTime;
		}
	}
}

double GlonassSatLocationEstimator::ephimeridicTime(double currentTime) const
{
	static const auto secondsInDay = 86400;
	currentTime += _storage->satTimeToMdv() - _storage->gamma() * (currentTime - _storage->timestamp());

	if (currentTime < 0)
		currentTime += secondsInDay;
	else
		while (currentTime > secondsInDay)
			currentTime -= secondsInDay;

	return currentTime;
}


std::array<double, 6> GlonassSatLocationEstimator::estimateDiff(const std::array<double, 6>& k, const std::array<double, 3>& rtt) const
{
	std::array<double, 6> arr;

	double A1 = 6378.136;
	double mu = 398600.44;
	double c20 = -1082.63e-6;
	double wz = 0.7292115e-4;

	double ae2 = pow(A1, 2);
	double w2 = pow(wz, 2);
	double r = sqrt(pow(k[0], 2) + pow(k[1], 2) + pow(k[2], 2));
	double r2 = pow(r, 2);
	double r3 = pow(r, 3);
	double r5 = pow(r, 5);
	double c1 = 3 * c20 * mu * ae2 / (2 * r5);
	double c2 = (-1) * mu / r3;
	double c3 = (5 * pow(k[2], 2) / r2);

	arr[0] = k[3];
	arr[1] = k[4];
	arr[2] = k[5];
	arr[3] = c2 * k[0] + c1 * k[0] * (1 - c3) + w2 * k[0] + 2 * wz * k[4] + rtt[0];
	arr[4] = c2 * k[1] + c1 * k[1] * (1 - c3) + w2 * k[1] - 2 * wz * k[3] + rtt[1];
	arr[5] = c2 * k[2] + c1 * k[2] * (3 - c3) + rtt[2];

	return arr;
}

Vector3 GlonassSatLocationEstimator::toGeocentric(const Vector3& vector)
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