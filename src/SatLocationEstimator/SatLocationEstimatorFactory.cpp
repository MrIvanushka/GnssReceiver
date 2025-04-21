#include "SatLocationEstimatorFactory.h"
#include "Log.h"

#include "GPSSatLocationEstimator.h"
#include "GlonassSatLocationEstimator.h"

using namespace gnssRecv::satLocationEstimator;

std::unique_ptr<ISatLocationEstimator> SatLocationEstimatorFactory::makeEstimator(
	std::shared_ptr<IEphemerisStorage> storage)
{
	switch (storage->type())
	{
	case ProtocolType::Glonass:
	{
		auto castedStorage = std::dynamic_pointer_cast<IGlonassEphemerisStorage>(storage);
		if (!castedStorage)
		{
			LOG_ERROR("Bad ephemeris storage format!");
			return nullptr;
		}
		return std::make_unique<GlonassSatLocationEstimator>(castedStorage);
	}
	case ProtocolType::GPS:
	{
		auto castedStorage = std::dynamic_pointer_cast<IGPSEphemerisStorage>(storage);
		if (!castedStorage)
		{
			LOG_ERROR("Bad ephemeris storage format!");
			return nullptr;
		}
		return std::make_unique<GPSSatLocationEstimator>(castedStorage);
	}
	case ProtocolType::BeiDou:
	{
		LOG_ERROR("Satellite location estimator doesn't support BeiDou");
		return nullptr;
	}
	case ProtocolType::Galileo:
	{
		LOG_ERROR("Satellite location estimator doesn't support Galileo");
		return nullptr;
	}
	default:
	{
		LOG_ERROR("Satellite location estimator doesn't support such format");
		return nullptr;
	}
	}
}