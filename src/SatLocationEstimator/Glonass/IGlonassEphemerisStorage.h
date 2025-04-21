#pragma once

#include "IEphemerisStorage.h"
#include <array>

namespace gnssRecv
{
namespace satLocationEstimator
{

class IGlonassEphemerisStorage : public IEphemerisStorage
{
public:
	ProtocolType type() const override { return ProtocolType::Glonass; }

	virtual double timestamp() const = 0;

	virtual const std::array<double, 6>& locationAndVelocity() const = 0;

	virtual const std::array<double, 3>& acceleration() const = 0;

	virtual double satTimeToMdv() const = 0;

	virtual double gamma() const = 0;

	virtual void updateLocationAndVelocity(
		const std::array<double, 6>& locationAndVelocity,
		double timestamp) = 0;
};

} //namespace satLocationEstimator

} //namespace gnssRecv