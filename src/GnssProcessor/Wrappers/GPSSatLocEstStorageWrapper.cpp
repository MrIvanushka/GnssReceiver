#include "GPSSatLocEstStorageWrapper.h"

using namespace gnssRecv;

GPSSatLocEstStorageWrapper::GPSSatLocEstStorageWrapper(
	std::shared_ptr<IGPSSatStorage> storage) :
	_storage(storage)
{}

double GPSSatLocEstStorageWrapper::timestamp() const
{
	return _storage->lastEphemeris().tOE();
}

double GPSSatLocEstStorageWrapper::meanAnomaly() const
{
	return _storage->lastEphemeris().m0() * _pi;
}

double GPSSatLocEstStorageWrapper::semiMajorAxis() const
{
	auto sqrt = _storage->lastEphemeris().sqrtOfA();
	return sqrt * sqrt;
}

double GPSSatLocEstStorageWrapper::eccentricity() const
{
	return _storage->lastEphemeris().e();
}

double GPSSatLocEstStorageWrapper::longtitudeOfAscendingNode() const
{
	return _storage->lastEphemeris().omega0() * _pi;
}

double GPSSatLocEstStorageWrapper::inclination() const
{
	return _storage->lastEphemeris().i0() * _pi;
}

double GPSSatLocEstStorageWrapper::argumentOfPerigee() const
{
	return _storage->lastEphemeris().omega() * _pi;
}

double GPSSatLocEstStorageWrapper::meanMotionDifference() const
{
	return _storage->lastEphemeris().deltaN() * _pi;
}

double GPSSatLocEstStorageWrapper::ascendingRate() const
{
	return _storage->lastEphemeris().ascendingRate() * _pi;
}

double GPSSatLocEstStorageWrapper::inclinationRate() const
{
	return _storage->lastEphemeris().inclinationRate() * _pi;
}

double GPSSatLocEstStorageWrapper::correctionSinPerigee() const
{
	return _storage->lastEphemeris().cUS();
}

double GPSSatLocEstStorageWrapper::correctionCosPerigee() const
{
	return _storage->lastEphemeris().cUC();
}

double GPSSatLocEstStorageWrapper::correctionSinRadial() const
{
	return _storage->lastEphemeris().cRS();
}

double GPSSatLocEstStorageWrapper::correctionCosRadial() const
{
	return _storage->lastEphemeris().cRC();
}

double GPSSatLocEstStorageWrapper::correctionSinInclination() const
{
	return _storage->lastEphemeris().cIS();
}

double GPSSatLocEstStorageWrapper::correctionCosInclination() const
{
	return _storage->lastEphemeris().cIC();
}