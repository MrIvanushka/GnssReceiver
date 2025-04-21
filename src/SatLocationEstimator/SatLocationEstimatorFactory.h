#pragma once

#include "IEphemerisStorage.h"
#include "ISatLocationEstimator.h"

namespace gnssRecv
{
namespace satLocationEstimator
{

class SatLocationEstimatorFactory
{
public:
	static std::unique_ptr<ISatLocationEstimator> makeEstimator(std::shared_ptr<IEphemerisStorage>);
};

} //namespace satLocationEstimator

} //namespace gnssRecv