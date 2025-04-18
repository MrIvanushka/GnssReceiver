#include "EphemerisProcessor.h"

#include "EphemerisHeader.h"
#include "Log.h"

EphemerisProcessor::EphemerisProcessor(std::shared_ptr<IGPSSatelliteStorage> storage) :
	_storage(storage)
{}

bool EphemerisProcessor::onData(ByteData& data, SubframeType type)
{
	switch (type)
	{
	case SubframeType::Ephemeris_1:
		return collectFirstFragment(data);
	case SubframeType::Ephemeris_2:
		return collectSecondFragment(data);
	default:
		LOG_ERROR("Unknown subframe type appeared in Ephemeris processor; type = ", static_cast<uint8_t>(type));
		return false;
	}
}

void EphemerisProcessor::clear()
{
	_collectedData.clear();
}

bool EphemerisProcessor::collectFirstFragment(ByteData& data)
{
	if (_collectedData.size() != 0)
	{
		LOG_WARN("Missed ending of previous Ephemeris message");
		return false;
	}

	_collectedData.clear();
	_collectedData = data;
	return data.size();
}

bool EphemerisProcessor::collectSecondFragment(ByteData& data)
{
	if (_collectedData.size() == 0)
	{
		LOG_WARN("Missed beginning of Ephemeris message");
		return false;
	}

	_collectedData.append(data);
	EphemerisHeader header;
	if (!_collectedData.castTo(&header))
	{
		LOG_ERROR("Ephemeris message is too short to be parsed!");
		return false;
	}

	_storage->setEphemeris(header);
	_collectedData.clear();

	return true;
}