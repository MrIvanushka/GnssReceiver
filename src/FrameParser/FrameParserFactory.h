#pragma once

#include "IFrameParser.h"
#include "ISatelliteStorage.h"

class FrameParserFactory
{
public:
	static std::unique_ptr<IFrameParser> makeParser(std::shared_ptr<ISatelliteStorage>);
};