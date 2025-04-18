#include "SubframeProcessor.h"

#include "HandoverWordHeader.h"
#include "SatClockProcessor.h"
#include "EphemerisProcessor.h"

SubframeProcessor::SubframeProcessor(std::shared_ptr<IGPSSatelliteStorage> storage) :
	_storage(storage),
	_satClockProcessor(std::make_shared<SatClockProcessor>(storage)),
	_ephemerisProcessor(std::make_shared<EphemerisProcessor>(storage))
{
}

bool SubframeProcessor::onData(ByteData& data)
{
	HandoverWordHeader how;

	if (!data.castToAndRemoveLeft(&how))
	{
		LOG_ERROR("Cannot cut HOW header; ByteData size = ", data.size());
		return false;
	}
	_storage->setZCounter(how.zCounter());

	auto type = static_cast<SubframeType>(how.subframeID());
	switch (type)
	{
	case SubframeType::SatClock:
		return _satClockProcessor->onData(data, type);
	case SubframeType::Ephemeris_1:
		return _ephemerisProcessor->onData(data, type);
	case SubframeType::Ephemeris_2:
		return _ephemerisProcessor->onData(data, type);
	case SubframeType::Almanac_1:
		return true;
	case SubframeType::Almanac_2:
		return true;
	}
	LOG_ERROR("Unknown Subframe ID = ", how.subframeID());

	return true;
}

void SubframeProcessor::clear()
{
	_satClockProcessor->clear();
	_ephemerisProcessor->clear();
}