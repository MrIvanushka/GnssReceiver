#pragma once

#include "ProtocolType.h"
#include "Vector3.h"

namespace gnssRecv
{

enum class TrackingState
{
	ACTIVE,
	COLLECTING_DATA,
	SYNCRONIZING,
	LOST
};

class ISatStorage
{
public:
	virtual ~ISatStorage() = default;

	virtual ProtocolType protocolType() const = 0;

	virtual TrackingState trackingState() const = 0;

	virtual math::Vector3 location() const = 0;

	virtual double satelliteTimeOfWeek() const = 0;

	virtual double interpolatedTime(double localTime) const = 0;

	virtual double lastReceiveLocalTime() const = 0;

	virtual uint64_t secondsUTC() const = 0;

	virtual void updateLocation(const math::Vector3& newLocation) = 0;

	virtual void handleNewSignalHappened(double timestamp) = 0;

	virtual void handleMissedSignal() = 0;

	virtual void handleSyncroError() = 0;

	virtual void handleSyncroSuccess() = 0;
};

} //namespace gnssRecv