#pragma once

#include "IGlonassEphemerisStorage.h"

class CommonGlonassEphemerisStorage : public IGlonassEphemerisStorage
{
public:
	CommonGlonassEphemerisStorage(
		double timestamp,
		const std::array<double, 6>& locationAndVelocity,
		const std::array<double, 3>& acceleration,
		double satTimeToMdv, double gamma) :
		_timestamp(timestamp), _locationAndVelocity(locationAndVelocity), _acceleration(acceleration),
		_satTimeToMdv(satTimeToMdv), _gamma(gamma)
	{}

	double timestamp() const override { return _timestamp; }

	const std::array<double, 6>& locationAndVelocity() const override { return _locationAndVelocity; }

	const std::array<double, 3>& acceleration() const override { return _acceleration; }

	double satTimeToMdv() const { return _satTimeToMdv; }

	double gamma() const { return _gamma; }

	void updateLocationAndVelocity(
		const std::array<double, 6>& locationAndVelocity,
		double timestamp) override
	{
		_locationAndVelocity = locationAndVelocity;
		_timestamp = timestamp;
	}
private:
	double _timestamp;
	std::array<double, 6> _locationAndVelocity;
	std::array<double, 3> _acceleration;

	double _satTimeToMdv;
	double _gamma;
};