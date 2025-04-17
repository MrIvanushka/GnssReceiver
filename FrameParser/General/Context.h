#pragma once

#include "HandoverWordHeader.h"
#include "SatClockHeader.h"
#include "EphemerisHeader.h"

class ISatelliteStorage
{
public:
	virtual ~ISatelliteStorage() = default;
};

class IContext
{
public:
	virtual ~IContext() = default;

	virtual std::shared_ptr<ISatelliteStorage> storage(PRN) = 0;
};

class GPSSatelliteStorage : public ISatelliteStorage
{
public:
	//TODO: make looking better

	HandoverWordHeader lastHow;
	SatClockHeader lastSatClock;
	EphemerisHeader lastEphemeris;
};

class GPSContext : public IContext
{
public:
	GPSContext();

	std::shared_ptr<ISatelliteStorage> storage(PRN) override;
private:
	std::vector<std::shared_ptr<ISatelliteStorage>> _storages;
};