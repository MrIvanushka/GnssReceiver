#pragma once

#include "Vector3.h"

class IReceiverLocationEstimator
{
public:
	typedef Vector3 Location;
	typedef double Time;

	virtual ~IReceiverLocationEstimator() = default;

	virtual std::pair<Location, Time> calculateLocation(double currentTime) = 0;
};