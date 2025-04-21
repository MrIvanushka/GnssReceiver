#pragma once

#include "ISatelliteTable.h"
#include "IReceiverLocationEstimator.h"

namespace gnssRecv
{
namespace receiverLocationEstimator
{

class ReceiverLocationEstimatorFactory
{
public:
	static std::unique_ptr<IReceiverLocationEstimator> makeEstimator(std::shared_ptr<ISatelliteTable>);
};

} //namespace receiverLocationEstimator

} //namespace gnssRecv