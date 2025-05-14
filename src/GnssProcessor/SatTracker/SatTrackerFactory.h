#pragma once

#include "SatTracker.h"
#include "ISatStorage.h"

namespace gnssRecv
{

class SatTrackerFactory
{
public:
	static SatTracker build(std::shared_ptr<ISatStorage>);
private:
	static SatTracker buildGPS(std::shared_ptr<ISatStorage>);
};

} //namespace gnssRecv