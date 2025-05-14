#pragma once

#include "IGPSSatStorage.h"
#include "IGPSEphemerisStorage.h"

namespace gnssRecv
{

class GPSSatLocEstStorageWrapper : public satLocationEstimator::IGPSEphemerisStorage
{
public:
	GPSSatLocEstStorageWrapper(std::shared_ptr<IGPSSatStorage>);

	double timestamp() const override;

	double meanAnomaly() const override;
	double semiMajorAxis() const override;
	double eccentricity() const override;
	double longtitudeOfAscendingNode() const override;
	double inclination() const override;
	double argumentOfPerigee() const override;

	double meanMotionDifference() const override;
	double ascendingRate() const override;
	double inclinationRate() const override;

	double correctionSinPerigee() const override;
	double correctionCosPerigee() const override;
	double correctionSinRadial() const override;
	double correctionCosRadial() const override;
	double correctionSinInclination() const override;
	double correctionCosInclination() const override;

	void setEccentricAnomaly(double value) override { _storage->setEccentricAnomaly(value); }
private:
	static inline const double _pi = 3.1415926535;

	std::shared_ptr<IGPSSatStorage> _storage;
};

} //namespace gnssRecv