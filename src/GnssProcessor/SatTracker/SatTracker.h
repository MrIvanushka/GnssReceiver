#pragma once

#include "IFrameParser.h"
#include "ISatLocationEstimator.h"
#include "IGnssStorage.h"

namespace gnssRecv
{

struct SatTracker
{
public:
	typedef frameParser::IFrameParser IFrameParser;
	typedef satLocationEstimator::ISatLocationEstimator ISatLocationEstimator;
public:
	std::shared_ptr<IFrameParser> frameParser = nullptr;
	std::shared_ptr<ISatLocationEstimator> locationEstimator = nullptr;
};

} //namespace gnssRecv