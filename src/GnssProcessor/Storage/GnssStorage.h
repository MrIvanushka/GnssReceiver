#pragma once

#include <unordered_map>

#include "IGnssStorage.h"

namespace gnssRecv
{

class GnssStorage : public IGnssStorage
{
public:
	GnssStorage(ProtocolType);

	ProtocolType protocolType() const override { return _protocolType; }

	std::deque<math::Vector3> receiverLocations() const override { return _receiverLocations; }

	void updateReceiverLocation(math::Vector3 r) override { _receiverLocations.push_back(r); }

	std::shared_ptr<ISatStorage> getSatStorage(PRN) override;

	std::shared_ptr<const ISatStorage> getSatStorage(PRN) const override;

	const std::vector<PRN>& availableSatellites() const override { return _availableSatellites; }
private:
	std::shared_ptr<ISatStorage> makeSatStorage(PRN);
private:
	ProtocolType _protocolType;

	std::unordered_map<PRN, std::shared_ptr<ISatStorage>> _satStorages;

	std::vector<PRN> _availableSatellites;

	std::deque<math::Vector3> _receiverLocations;
};

} //namespace gnssRecv