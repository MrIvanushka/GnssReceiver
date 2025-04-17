#pragma once

#include "IDataProcessor.h"
#include "Context.h"

class SatClockProcessor : public IDataProcessor
{
public:
	SatClockProcessor(std::shared_ptr<GPSSatelliteStorage>);

	bool onData(ByteData&, SubframeType) override;
private:
	std::shared_ptr<GPSSatelliteStorage> _storage;
};