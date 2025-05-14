#pragma once

#include "ISatStorage.h"
#include "HandoverWordHeader.h"
#include "EphemerisHeader.h"
#include "SatClockHeader.h"

namespace gnssRecv
{

class IGPSSatStorage : public ISatStorage
{
public:
	ProtocolType protocolType() const override { return ProtocolType::GPS; }

	virtual void setZCounter(uint32_t) = 0;

	virtual void setSatClock(const frameParser::SatClockHeader&) = 0;

	virtual void setEphemeris(const frameParser::EphemerisHeader&) = 0;

	virtual void setEccentricAnomaly(double value) = 0;

	virtual uint32_t zCounter() const = 0;

	virtual const frameParser::SatClockHeader& lastSatClock() const = 0;

	virtual const frameParser::EphemerisHeader& lastEphemeris() const = 0;
};

} //namespace gnssRecv