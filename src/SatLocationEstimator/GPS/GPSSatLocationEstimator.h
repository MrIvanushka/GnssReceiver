#pragma once

#include "ISatLocationEstimator.h"
#include "IGPSEphemerisStorage.h"

#include "DenseMatrix.h"

namespace gnssRecv
{
namespace satLocationEstimator
{

class GPSSatLocationEstimator : public ISatLocationEstimator
{
public:
	GPSSatLocationEstimator(std::shared_ptr<IGPSEphemerisStorage>);

	math::Vector3 calculateLocation(double currentTime) override;
private:
	double calculateMeanAnomaly(double deltaTime) const;

	double calculateEccentricAnomaly(double meanAnomaly) const;

	double calculateTrueAnomaly(double eccentricAnomaly) const;

	double calculateAscending(double deltaTime) const;

	double calculateArgumentOfPerigee(double trueAnomaly) const;

	double calculateInclination(double deltaTime, double trueAnomaly) const;

	double calculateRadialDistance(double trueAnomaly, double eccentricAnomaly) const;

	math::DenseMatrix<double> r1(double angle) const;

	math::DenseMatrix<double> r3(double angle) const;
private:
	std::shared_ptr<IGPSEphemerisStorage> _storage;
};

} //namespace satLocationEstimator

} //namespace gnssRecv