#include "SubframeProcessor.h"

#include "HandoverWordHeader.h"
#include "SatClockProcessor.h"
#include "EphemerisProcessor.h"

using namespace gnssRecv::frameParser;

typedef FrameParserStatNames::FrameParserStatKey UsedStatKey;

SubframeProcessor::SubframeProcessor(std::shared_ptr<IGPSSatelliteStorage> storage) :
	_storage(storage),
	_satClockProcessor(std::make_shared<SatClockProcessor>(storage)),
	_ephemerisProcessor(std::make_shared<EphemerisProcessor>(storage))
{
	auto& statNames = FrameParserStatNames::names;

	std::unordered_map<StatKey, std::string> usedNames =
	{
		{ UsedStatKey::ReceivedSubframes, statNames[UsedStatKey::ReceivedSubframes] },
		{ UsedStatKey::ProducedSatClock, statNames[UsedStatKey::ProducedSatClock] },
		{ UsedStatKey::ProducedEphemeris1, statNames[UsedStatKey::ProducedEphemeris1] },
		{ UsedStatKey::ProducedEphemeris2, statNames[UsedStatKey::ProducedEphemeris2] },
		{ UsedStatKey::ProducedAlmanac1, statNames[UsedStatKey::ProducedAlmanac1] },
		{ UsedStatKey::ProducedAlmanac2, statNames[UsedStatKey::ProducedAlmanac2] }
	};

	_stat = Stat(statNames[UsedStatKey::SubframeParserStat], usedNames);
}

bool SubframeProcessor::onData(ByteData& data)
{
	_stat.increment(UsedStatKey::ReceivedSubframes);
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
		_stat.increment(UsedStatKey::ProducedSatClock);
		return _satClockProcessor->onData(data, type);
	case SubframeType::Ephemeris_1:
		_stat.increment(UsedStatKey::ProducedEphemeris1);
		return _ephemerisProcessor->onData(data, type);
	case SubframeType::Ephemeris_2:
		_stat.increment(UsedStatKey::ProducedEphemeris2);
		return _ephemerisProcessor->onData(data, type);
	case SubframeType::Almanac_1:
		_stat.increment(UsedStatKey::ProducedAlmanac1);
		return true;
	case SubframeType::Almanac_2:
		_stat.increment(UsedStatKey::ProducedAlmanac2);
		return true;
	}
	LOG_ERROR("Unknown Subframe ID = ", how.subframeID());

	return true;
}

void SubframeProcessor::clear()
{
	_satClockProcessor->clear();
	_ephemerisProcessor->clear();
	_stat.clear();
}