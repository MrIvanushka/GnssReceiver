#pragma once

#include "IDataProcessor.h"
#include "IGPSSatelliteStorage.h"

class SatClockProcessor : public IDataProcessor
{
public:
	SatClockProcessor(std::shared_ptr<IGPSSatelliteStorage>);

	bool onData(ByteData&, SubframeType) override;

	void clear() override;
private:
	std::shared_ptr<IGPSSatelliteStorage> _storage;
};