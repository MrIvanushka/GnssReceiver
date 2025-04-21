#pragma once

#include "Vector3.h"

namespace gnssRecv
{
namespace satLocationEstimator
{

class ISatLocationEstimator
{
public:
	virtual ~ISatLocationEstimator() = default;

	virtual math::Vector3 calculateLocation(double currentTime) = 0;
};

} //namespace satLocationEstimator

} //namespace gnssRecv