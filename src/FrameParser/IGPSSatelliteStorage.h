#pragma once

#include "ISatelliteStorage.h"

#include "SatClockHeader.h"
#include "EphemerisHeader.h"

namespace gnssRecv
{
namespace frameParser
{

class IGPSSatelliteStorage : public ISatelliteStorage
{
public:
	ProtocolType type() const override { return ProtocolType::GPS; }

	virtual void setZCounter(uint32_t value) = 0;
	virtual void setSatelliteClock(const SatClockHeader&) = 0;
	virtual void setEphemeris(const EphemerisHeader&) = 0;
};

} //namespace frameParser

} //namespace gnssRecv