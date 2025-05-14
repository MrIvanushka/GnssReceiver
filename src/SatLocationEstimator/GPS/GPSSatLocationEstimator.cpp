#include "GPSSatLocationEstimator.h"

using namespace gnssRecv::satLocationEstimator;
using gnssRecv::math::Vector3;
using gnssRecv::math::DenseMatrix;

GPSSatLocationEstimator::GPSSatLocationEstimator(
	std::shared_ptr<IGPSEphemerisStorage> storage) :
	_storage(storage)
{}

/* ================= основная функция ====================== */
Vector3 GPSSatLocationEstimator::calculateLocation(double currentTime)
{
	const double GM = 3.986005e14;
	const double OMEGA_E = 7.2921151467e-5;

	double tk = currentTime - _storage->timestamp();
	if (tk > 302400) tk -= 604800;          // прыжок через неделю
	if (tk < -302400) tk += 604800;

	/* 1. Средняя аномалия */
	double A = _storage->semiMajorAxis();
	double n0 = std::sqrt(GM / (A * A * A));
	double n = n0 + _storage->meanMotionDifference();
	double Mk = _storage->meanAnomaly() + n * tk;

	/* 2. Эллиптическая и истинная аномалия */
	double Ek = calculateEccentricAnomaly(Mk);
	_storage->setEccentricAnomaly(Ek);
	double sinE = std::sin(Ek), cosE = std::cos(Ek);
	double nu = std::atan2(std::sqrt(1 - _storage->eccentricity() * _storage->eccentricity()) * sinE, cosE - _storage->eccentricity());

	/* 3. Аргумент широты, радиус, наклонение */
	double phi = nu + _storage->argumentOfPerigee();

	double sin2phi = std::sin(2 * phi), cos2phi = std::cos(2 * phi);
	double du = _storage->correctionSinPerigee() * sin2phi + _storage->correctionCosPerigee() * cos2phi;
	double dr = _storage->correctionSinRadial() * sin2phi + _storage->correctionCosRadial() * cos2phi;
	double di = _storage->correctionSinInclination() * sin2phi + _storage->correctionCosInclination() * cos2phi;

	double u = phi + du;
	double r = A * (1 - _storage->eccentricity() * cosE) + dr;
	double i = _storage->inclination() + di + _storage->inclinationRate() * tk;

	/* 4. Положение в орбитальной системе */
	double x_orb = r * std::cos(u);
	double y_orb = r * std::sin(u);

	/* 5. Долгота восходящего узла */
	double Omega = _storage->longtitudeOfAscendingNode() + (_storage->ascendingRate() - OMEGA_E) * tk - OMEGA_E * _storage->timestamp();

	/* 6. Переход в ECEF */
	double cosO = std::cos(Omega), sinO = std::sin(Omega);
	double cosi = std::cos(i), sini = std::sin(i);

	return math::Vector3(x_orb * cosO - y_orb * cosi * sinO, x_orb * sinO + y_orb * cosi * cosO, y_orb * sini);
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