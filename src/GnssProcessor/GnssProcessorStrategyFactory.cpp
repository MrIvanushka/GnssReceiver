#include "GnssProcessorStrategyFactory.h"

#include "GnssProcessorStrategy.h"
#include "GnssStorage.h"

using namespace gnssRecv;

std::unique_ptr<IGnssProcessorStrategy> GnssProcessorStrategyFactory::makeStrategy(ProtocolType protocol)
{
	auto storage = std::make_shared<GnssStorage>(protocol);
	return std::make_unique<GnssProcessorStrategy>(storage);
}