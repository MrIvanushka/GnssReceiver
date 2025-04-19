#pragma once

#include "IGPSEphemerisStorage.h"

class CommonGPSEphemerisStorage : public IGPSEphemerisStorage
{
public:
	CommonGPSEphemerisStorage(
		double timestamp, double meanAnomaly, double semiMajor, double eccentricity,
		double longtitudeOfAscendingNode, double inclination, double argumentOfPerigee,
		double meanMotionDifference, double ascendingRate, double inclinationRate,
		double correctionSinPerigee, double correctionCosPerigee, double correctionSinRadial,
		double correctionCosRadial, double correctionSinInclination, double correctionCosInclination) :
		_timestamp(timestamp), _meanAnomaly(meanAnomaly), _semiMajor(semiMajor), _eccentricity(eccentricity),
		_longtitudeOfAscendingNode(longtitudeOfAscendingNode), _inclination(inclination),
		_argumentOfPerigee(argumentOfPerigee), _meanMotionDifference(meanMotionDifference),
		_ascendingRate(ascendingRate), _inclinationRate(inclinationRate),
		_correctionSinPerigee(correctionSinPerigee), _correctionCosPerigee(correctionCosPerigee),
		_correctionSinRadial(correctionSinRadial), _correctionCosRadial(correctionCosRadial),
		_correctionSinInclination(correctionSinInclination), _correctionCosInclination(correctionCosInclination)
	{ }

	double timestamp() const override { return _timestamp; }

	double meanAnomaly() const override { return _meanAnomaly; }
	double semiMajorAxis() const override { return _semiMajor; }
	double eccentricity() const override { return _eccentricity; }
	double longtitudeOfAscendingNode() const override { return _longtitudeOfAscendingNode; }
	double inclination() const override { return _inclination; }
	double argumentOfPerigee() const override { return _argumentOfPerigee; }

	double meanMotionDifference() const override { return _meanMotionDifference; }
	double ascendingRate() const override { return _ascendingRate; }
	double inclinationRate() const override { return _inclinationRate; }

	double correctionSinPerigee() const override { return _correctionSinPerigee; }
	double correctionCosPerigee() const override { return _correctionCosPerigee; }
	double correctionSinRadial() const override { return _correctionSinRadial; }
	double correctionCosRadial() const override { return _correctionCosRadial; }
	double correctionSinInclination() const override { return _correctionSinInclination; }
	double correctionCosInclination() const override { return _correctionCosInclination; }
private:
	double _timestamp;
	double _meanAnomaly;
	double _semiMajor;
	double _eccentricity;
	double _longtitudeOfAscendingNode;
	double _inclination;
	double _argumentOfPerigee;
	double _meanMotionDifference;
	double _ascendingRate;
	double _inclinationRate;

	double _correctionSinPerigee;
	double _correctionCosPerigee;
	double _correctionSinRadial;
	double _correctionCosRadial;
	double _correctionSinInclination;
	double _correctionCosInclination;
};