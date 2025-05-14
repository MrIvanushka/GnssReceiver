#pragma once

#include "ProtocolType.h"
#include "ISatStorage.h"
#include <memory>
#include <vector>
#include <deque>

namespace gnssRecv
{

class IGnssStorage
{
public:
	typedef uint32_t PRN;
public:
	virtual ~IGnssStorage() = default;

	virtual ProtocolType protocolType() const = 0;

	virtual std::deque<math::Vector3> receiverLocations() const = 0;

	virtual void updateReceiverLocation(math::Vector3) = 0;

	virtual std::shared_ptr<ISatStorage> getSatStorage(PRN) = 0;

	virtual std::shared_ptr<const ISatStorage> getSatStorage(PRN) const = 0;

	virtual const std::vector<PRN>& availableSatellites() const = 0;
};


} //namespace gnssRecv