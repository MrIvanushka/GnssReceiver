#include "SatClockProcessor.h"

#include "SatClockHeader.h"

SatClockProcessor::SatClockProcessor(std::shared_ptr<GPSSatelliteStorage> storage) :
	_storage(storage)
{}

bool SatClockProcessor::onData(ByteData& data, SubframeType type)
{
	SatClockHeader header;
	if (!data.castTo(&header))
	{
		LOG_ERROR("Sat Clock message is too short to be parsed!");
		return false;
	}
	_storage->lastSatClock = header;
	return true;
}