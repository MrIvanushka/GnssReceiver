#pragma once

#include "IEphemerisStorage.h"

namespace gnssRecv
{
namespace satLocationEstimator
{

class IGPSEphemerisStorage : public IEphemerisStorage
{
public:
	ProtocolType type() const override { return ProtocolType::GPS; }

	virtual double timestamp() const = 0;

	virtual double meanAnomaly() const = 0;
	virtual double semiMajorAxis() const = 0;
	virtual double eccentricity() const = 0;
	virtual double longtitudeOfAscendingNode() const = 0;
	virtual double inclination() const = 0;
	virtual double argumentOfPerigee() const = 0;

	virtual double meanMotionDifference() const = 0;
	virtual double ascendingRate() const = 0;
	virtual double inclinationRate() const = 0;

	virtual double correctionSinPerigee() const = 0;
	virtual double correctionCosPerigee() const = 0;
	virtual double correctionSinRadial() const = 0;
	virtual double correctionCosRadial() const = 0;
	virtual double correctionSinInclination() const = 0;
	virtual double correctionCosInclination() const = 0;

	virtual void setEccentricAnomaly(double value) = 0;
};

} //namespace satLocationEstimator

} //namespace gnssRecv