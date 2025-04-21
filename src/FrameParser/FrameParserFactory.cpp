#include "FrameParserFactory.h"

#include "GPSFrameParser.h"
#include "IGPSSatelliteStorage.h"

using namespace gnssRecv::frameParser;

std::unique_ptr<IFrameParser> FrameParserFactory::makeParser(std::shared_ptr<ISatelliteStorage> storage)
{
	//GPS
	auto gpsStorage = std::dynamic_pointer_cast<IGPSSatelliteStorage>(storage);
	if (gpsStorage)
	{
		return std::make_unique<GPSFrameParser>(gpsStorage);
	}
	//GLONASS - TODO

	LOG_ERROR("Given navigation frame protocol is not supported");
	return nullptr;
}