#pragma once

#include "Vector3.h"

class ISatLocationEstimator
{
public:
	virtual ~ISatLocationEstimator() = default;

	virtual Vector3 calculateLocation(double currentTime) = 0;
};