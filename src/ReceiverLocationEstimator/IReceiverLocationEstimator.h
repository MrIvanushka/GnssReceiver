#pragma once

#include "Vector3.h"

namespace gnssRecv
{
namespace receiverLocationEstimator
{

class IReceiverLocationEstimator
{
public:
	typedef math::Vector3 Location;
	typedef double Time;

	virtual ~IReceiverLocationEstimator() = default;

	virtual std::pair<Location, Time> calculateLocation(double currentTime) = 0;
};

} //namespace receiverLocationEstimator

} //namespace gnssRecv