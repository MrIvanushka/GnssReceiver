#pragma once

#include <memory>

#include "IDataInput.h"
#include "IGnssStorage.h"
#include "Stat.h"

namespace gnssRecv
{

class IGnssProcessor
{
public:
	virtual ~IGnssProcessor() = default;

	virtual void start(ProtocolType, std::shared_ptr<IDataInput>) = 0;

	virtual void stop() = 0;

	virtual bool running() const = 0;

	virtual std::shared_ptr<const IGnssStorage> storage() const = 0;

	virtual std::vector<Stat> satelliteStat(int PRN) const = 0;
};

} //namespace gnssRecv