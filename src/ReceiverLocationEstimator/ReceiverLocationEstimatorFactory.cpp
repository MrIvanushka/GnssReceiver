#include "ReceiverLocationEstimatorFactory.h"
#include "Log.h"
#include "CommonReceiverLocationEstimator.h"

std::unique_ptr<IReceiverLocationEstimator> ReceiverLocationEstimatorFactory::makeEstimator(
	std::shared_ptr<ISatelliteTable> storage)
{
	switch (storage->type())
	{
	case ProtocolType::Glonass:
	case ProtocolType::GPS:
		return std::make_unique<CommonReceiverLocationEstimator>(storage);
	case ProtocolType::BeiDou:
	{
		LOG_ERROR("Receiver location estimator doesn't support BeiDou");
		return nullptr;
	}
	case ProtocolType::Galileo:
	{
		LOG_ERROR("Receiver location estimator doesn't support Galileo");
		return nullptr;
	}
	default:
	{
		LOG_ERROR("Receiver location estimator doesn't support such format");
		return nullptr;
	}
	}
}