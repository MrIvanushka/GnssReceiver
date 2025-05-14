#pragma once

#include "Vector3.h"
#include "ProtocolType.h"
#include <vector>

namespace gnssRecv
{
namespace receiverLocationEstimator
{

class ISatelliteParams
{
public:
	virtual ~ISatelliteParams() = default;

	virtual double satTime(double currentTime) const = 0;

	virtual math::Vector3 location() const = 0;
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

} //namespace receiverLocationEstimator

} //namespace gnssRecv