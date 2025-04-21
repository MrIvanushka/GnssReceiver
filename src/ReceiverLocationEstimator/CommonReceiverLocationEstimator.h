#pragma once

#include "IReceiverLocationEstimator.h"
#include "ISatelliteTable.h"

namespace gnssRecv
{
namespace receiverLocationEstimator
{

class CommonReceiverLocationEstimator : public IReceiverLocationEstimator
{
public:
	CommonReceiverLocationEstimator(std::shared_ptr<ISatelliteTable>);

	std::pair<Location, Time> calculateLocation(double currentTime) override;
private:
	std::shared_ptr<ISatelliteTable> _storage;
};

} //namespace receiverLocationEstimator

} //namespace gnssRecv