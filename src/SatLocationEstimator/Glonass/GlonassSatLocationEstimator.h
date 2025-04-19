#pragma once

#include "ISatLocationEstimator.h"
#include "IGlonassEphemerisStorage.h"

class GlonassSatLocationEstimator : public ISatLocationEstimator
{
public:
	GlonassSatLocationEstimator(std::shared_ptr<IGlonassEphemerisStorage>);

	Vector3 calculateLocation(double currentTime) override;
private:
	double ephimeridicTime(double currentTime) const;

	void estimateRungeKutta(
		std::array<double, 6>& locationAndVelocity,
		const std::array<double, 3>& acceleration,
		double deltaTime) const;

	std::array<double, 6> estimateDiff(
		const std::array<double, 6>& k,
		const std::array<double, 3>& rtt) const;

	Vector3 toGeocentric(const Vector3& vector);
private:
	std::shared_ptr<IGlonassEphemerisStorage> _storage;
};