#pragma once

#include "IEphemerisStorage.h"
#include "ISatLocationEstimator.h"

class SatLocationEstimatorFactory
{
public:
	static std::unique_ptr<ISatLocationEstimator> makeEstimator(std::shared_ptr<IEphemerisStorage>);
};