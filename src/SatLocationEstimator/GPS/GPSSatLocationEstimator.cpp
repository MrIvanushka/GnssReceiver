#include "GPSSatLocationEstimator.h"

GPSSatLocationEstimator::GPSSatLocationEstimator(
	std::shared_ptr<IGPSEphemerisStorage> storage) :
	_storage(storage)
{}

Vector3 GPSSatLocationEstimator::calculateLocation(double currentTime)
{
	auto deltaTime = currentTime - _storage->timestamp();

	auto meanAnomaly = calculateMeanAnomaly(deltaTime);
	auto eccentricAnomaly = calculateEccentricAnomaly(meanAnomaly);
	auto trueAnomaly = calculateTrueAnomaly(eccentricAnomaly);
	auto argumentOfAscendingNode = calculateAscending(deltaTime);
	auto argumentOfPerigee = calculateArgumentOfPerigee(trueAnomaly);
	auto inclination = calculateInclination(deltaTime, trueAnomaly);
	auto radialDistance = calculateRadialDistance(trueAnomaly, eccentricAnomaly);

	std::vector<double> selfSystemCoords = 
	{ 
		radialDistance * cos(trueAnomaly),
		radialDistance * sin(trueAnomaly),
		0
	};
	auto geocentricCoords = r1(-argumentOfAscendingNode) * r3(-inclination) * r1(-argumentOfPerigee) * selfSystemCoords;

	return Vector3(geocentricCoords[0], geocentricCoords[1], geocentricCoords[2]);
}

double GPSSatLocationEstimator::calculateMeanAnomaly(double deltaTime) const
{
	static const double earthGravitationParameter = 398'600'441'800'000;

	auto keplerianFactor = (sqrt(earthGravitationParameter / pow(_storage->semiMajorAxis(), 3)));
	return _storage->meanAnomaly() + (keplerianFactor + _storage->meanMotionDifference()) * deltaTime;
}

double GPSSatLocationEstimator::calculateEccentricAnomaly(double meanAnomaly) const
{
	auto eccentricity = _storage->eccentricity();
	double eccentricAnomaly = 1;
	const double quality = 1e-12;
	for (auto i = 0u; i < 20; ++i)
	{
		auto previousVal = eccentricAnomaly;
		eccentricAnomaly = meanAnomaly + eccentricity * sin(eccentricAnomaly);

		if (abs(previousVal - eccentricAnomaly) < quality)
			break;
	}
	return eccentricAnomaly;
}

double GPSSatLocationEstimator::calculateTrueAnomaly(double eccentricAnomaly) const
{
	auto eccentricity = _storage->eccentricity();
	auto multiplier = sqrt(1 - eccentricity * eccentricity);

	return (multiplier * sin(eccentricAnomaly)) / (cos(eccentricAnomaly) - eccentricity);
}

double GPSSatLocationEstimator::calculateAscending(double deltaTime) const
{
	static const double earthAngularSpeed = 7.2921151467e-5;

	auto ascendingDelta = (_storage->ascendingRate() - earthAngularSpeed) * deltaTime;
	auto earthInitialFactor = earthAngularSpeed * _storage->timestamp();
	return _storage->longtitudeOfAscendingNode() + ascendingDelta - earthInitialFactor;
}

double GPSSatLocationEstimator::calculateArgumentOfPerigee(double trueAnomaly) const
{
	auto correctionArg = 2 * (_storage->argumentOfPerigee() + trueAnomaly);
	auto cosCorrection = _storage->correctionCosPerigee() * cos(correctionArg);
	auto sinCorrection = _storage->correctionSinPerigee() * sin(correctionArg);
	return _storage->argumentOfPerigee() + trueAnomaly + cosCorrection + sinCorrection;
}

double GPSSatLocationEstimator::calculateInclination(double deltaTime, double trueAnomaly) const
{
	auto correctionArg = 2 * (_storage->argumentOfPerigee() + trueAnomaly);
	auto cosCorrection = _storage->correctionCosInclination() * cos(correctionArg);
	auto sinCorrection = _storage->correctionSinInclination() * sin(correctionArg);
	auto inclinationShift = _storage->inclinationRate() * deltaTime;
	return _storage->inclination() + correctionArg + cosCorrection + sinCorrection;
}

double GPSSatLocationEstimator::calculateRadialDistance(double trueAnomaly, double eccentricAnomaly) const
{
	auto correctionArg = 2 * (_storage->argumentOfPerigee() + trueAnomaly);
	auto cosCorrection = _storage->correctionCosRadial() * cos(correctionArg);
	auto sinCorrection = _storage->correctionSinRadial() * sin(correctionArg);
	auto eccentricMultiplier = 1 - _storage->eccentricity() * cos(eccentricAnomaly);
	return _storage->semiMajorAxis() * eccentricMultiplier + cosCorrection + sinCorrection;
}

DenseMatrix<double> GPSSatLocationEstimator::r1(double angle) const
{
	std::vector<double> values = 
	{ 
		cos(angle), sin(angle), 0,
		-sin(angle), cos(angle), 0,
		0, 0, 1
	};
	return DenseMatrix<double>(3, 3, values);
}

DenseMatrix<double> GPSSatLocationEstimator::r3(double angle) const
{
	std::vector<double> values =
	{
		1, 0, 0,
		0, cos(angle), sin(angle),
		0, -sin(angle), cos(angle),
	};
	return DenseMatrix<double>(3, 3, values);
}