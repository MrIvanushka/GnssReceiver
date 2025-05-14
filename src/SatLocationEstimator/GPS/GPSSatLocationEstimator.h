#pragma once

#include "ISatLocationEstimator.h"
#include "IGPSEphemerisStorage.h"

#include "DenseMatrix.h"
#include "Vector3.h"

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
	double calculateEccentricAnomaly(double meanAnomaly) const;
private:
	std::shared_ptr<IGPSEphemerisStorage> _storage;
};

} //namespace satLocationEstimator

} //namespace gnssRecv