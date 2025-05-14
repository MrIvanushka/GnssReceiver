#include "GPSFrameParserStorageWrapper.h"

using namespace gnssRecv;

GPSFrameParserStorageWrapper::GPSFrameParserStorageWrapper(
	std::shared_ptr<IGPSSatStorage> storage) :
	_storage(storage)
{ 
}

void GPSFrameParserStorageWrapper::setZCounter(uint32_t value)
{
	_storage->setZCounter(value);
}

void GPSFrameParserStorageWrapper::setSatelliteClock(const frameParser::SatClockHeader& msg)
{
	_storage->setSatClock(msg);
}

void GPSFrameParserStorageWrapper::setEphemeris(const frameParser::EphemerisHeader& msg)
{
	_storage->setEphemeris(msg);
}