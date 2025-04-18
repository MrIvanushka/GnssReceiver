#pragma once

#include "IGPSSatelliteStorage.h"

class CommonGPSSatelliteStorage : public IGPSSatelliteStorage
{
public:
	void setZCounter(uint32_t value) { _zCounter = value; }
	void setSatelliteClock(const SatClockHeader& head) { _satelliteClock = head; }
	void setEphemeris(const EphemerisHeader& head) { _ephemeris = head; }

	uint32_t zCounter() const { return _zCounter; }
	const SatClockHeader& satelliteClock() const { return _satelliteClock; }
	const EphemerisHeader& ephemeris() const { return _ephemeris; }
private:
	uint32_t _zCounter;
	SatClockHeader _satelliteClock;
	EphemerisHeader _ephemeris;
};