#pragma once

#include "Vector3.h"
#include "ProtocolType.h"
#include <vector>

class ISatelliteParams
{
public:
	virtual ~ISatelliteParams() = default;

	virtual double pseudoDelay() const = 0;

	virtual Vector3 location() const = 0;
};

class ISatelliteTable
{
public:
	typedef uint8_t PRN;
	typedef std::shared_ptr<ISatelliteParams> SatParamsPtr;

	virtual ~ISatelliteTable() = default;

	virtual ProtocolType type() const = 0;

	virtual const std::vector<SatParamsPtr> satelliteParams() const = 0;
};