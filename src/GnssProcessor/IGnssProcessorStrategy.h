#pragma once

#include <thread>

#include "IGnssStorage.h"
#include "Stat.h"

namespace gnssRecv
{

class IGnssProcessorStrategy
{
public:
	virtual ~IGnssProcessorStrategy() = default;

	virtual void receiveSignal(double signal, double timestamp, int PRN) = 0;

	virtual void updateReceiverLocation() = 0;

	virtual void clear() = 0;

	virtual std::shared_ptr<const IGnssStorage> storage() const = 0;

	virtual std::vector<Stat> satelliteStat(int PRN) const = 0;
};

} //namespace gnssRecv