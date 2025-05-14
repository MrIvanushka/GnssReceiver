#pragma once

#include "IGnssStorage.h"
#include "ISatelliteTable.h"

namespace gnssRecv
{

class SatParamsWrapper : public receiverLocationEstimator::ISatelliteParams
{
public:
	SatParamsWrapper(std::shared_ptr<ISatStorage>);

	double satTime(double localTime) const override;

	math::Vector3 location() const override;
private:
	std::shared_ptr<ISatStorage> _storage;
};

class RecvEstStorageWrapper : public receiverLocationEstimator::ISatelliteTable
{
public:
	RecvEstStorageWrapper(std::shared_ptr<IGnssStorage>);

	ProtocolType type() const override { return _storage->protocolType(); }

	const std::vector<SatParamsPtr> satelliteParams() const;
private:
	std::shared_ptr<IGnssStorage> _storage;
};

} //namespace gnssRecv