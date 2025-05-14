#include "SatTrackerFactory.h"

#include "FrameParserFactory.h"
#include "SatLocationEstimatorFactory.h"
#include "GPSFrameParserStorageWrapper.h"
#include "GPSSatLocEstStorageWrapper.h"

using namespace gnssRecv;

SatTracker SatTrackerFactory::build(std::shared_ptr<ISatStorage> storage)
{
	SatTracker ret;

	switch (storage->protocolType())
	{
	case ProtocolType::GPS:
		return buildGPS(storage);
	case ProtocolType::Glonass:
		LOG_ERROR("GNSS Processor doesn't support GLONASS");
		return ret;
	case ProtocolType::BeiDou:
		LOG_ERROR("GNSS Processor doesn't support BeiDou");
		return ret;
	case ProtocolType::Galileo:
		LOG_ERROR("GNSS Processor doesn't support Galileo");
		return ret;
	default:
		LOG_ERROR("GNSS Processor doesn't support such format");
		return ret;
	}
}

SatTracker SatTrackerFactory::buildGPS(std::shared_ptr<ISatStorage> storage)
{
	SatTracker ret;

	auto castedStorage = std::dynamic_pointer_cast<IGPSSatStorage>(storage);
	if (!castedStorage)
	{
		LOG_ERROR("Cannot cast Sat Storage!");
		return ret;
	}
	auto frameParserWrapper = std::make_shared<GPSFrameParserStorageWrapper>(castedStorage);
	ret.frameParser = frameParser::FrameParserFactory::makeParser(frameParserWrapper);

	auto satLocEstimatorWrapper = std::make_shared<GPSSatLocEstStorageWrapper>(castedStorage);
	ret.locationEstimator = satLocationEstimator::SatLocationEstimatorFactory::makeEstimator(satLocEstimatorWrapper);

	return ret;
}