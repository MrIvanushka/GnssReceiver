#pragma once

#include "ISatelliteStorage.h"

#include "SatClockHeader.h"
#include "EphemerisHeader.h"

class IGPSSatelliteStorage : public ISatelliteStorage
{
public:
	virtual void setZCounter(uint32_t value) = 0;
	virtual void setSatelliteClock(const SatClockHeader&) = 0;
	virtual void setEphemeris(const EphemerisHeader&) = 0;
};