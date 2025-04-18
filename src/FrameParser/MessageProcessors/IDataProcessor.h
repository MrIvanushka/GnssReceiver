#pragma once

#include "ByteData.h"

enum class SubframeType : uint8_t
{
	SatClock = 1,
	Ephemeris_1 = 2,
	Ephemeris_2 = 3,
	Almanac_1 = 4,
	Almanac_2 = 5
};

class IDataProcessor
{
public:
	virtual ~IDataProcessor() = default;

	virtual bool onData(ByteData&, SubframeType) = 0;

	virtual void clear() = 0;
};