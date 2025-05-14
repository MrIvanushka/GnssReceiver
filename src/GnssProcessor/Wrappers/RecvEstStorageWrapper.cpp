#include "RecvEstStorageWrapper.h"

using namespace gnssRecv;

SatParamsWrapper::SatParamsWrapper(std::shared_ptr<ISatStorage> storage) :
	_storage(storage)
{ }

double SatParamsWrapper::satTime(double currentTime) const
{
	return _storage->interpolatedTime(currentTime);
}

math::Vector3 SatParamsWrapper::location() const
{
	return _storage->location();
}

RecvEstStorageWrapper::RecvEstStorageWrapper(std::shared_ptr<IGnssStorage> storage) :
	_storage(storage)
{ }

const std::vector<RecvEstStorageWrapper::SatParamsPtr> RecvEstStorageWrapper::satelliteParams() const
{
	std::vector<SatParamsPtr> ret;

	for (auto prn : _storage->availableSatellites())
	{
		auto satStorage = _storage->getSatStorage(prn);
		if (satStorage->trackingState() == TrackingState::ACTIVE)
		{
			ret.push_back(std::make_shared<SatParamsWrapper>(satStorage));
		}
	}

	return ret;
}