#pragma once

#include "IFrameParser.h"
#include "ISatelliteStorage.h"

namespace gnssRecv
{
namespace frameParser
{

class FrameParserFactory
{
public:
	static std::unique_ptr<IFrameParser> makeParser(std::shared_ptr<ISatelliteStorage>);
};

} //namespace frameParser

} //namespace gnssRecv