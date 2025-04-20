#pragma once

#include "ISatelliteTable.h"
#include "IReceiverLocationEstimator.h"

class ReceiverLocationEstimatorFactory
{
public:
	static std::unique_ptr<IReceiverLocationEstimator> makeEstimator(std::shared_ptr<ISatelliteTable>);
};