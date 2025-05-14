#pragma once

#include "IGnssProcessorStrategy.h"

namespace gnssRecv
{

class GnssProcessorStrategyFactory
{
public:
	static std::unique_ptr<IGnssProcessorStrategy> makeStrategy(ProtocolType);
};

} //namespace gnssRecv