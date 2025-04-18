#pragma once

#include "IDataProcessor.h"
#include "IGPSSatelliteStorage.h"
#include <memory>

class SubframeProcessor
{
public:
	SubframeProcessor(std::shared_ptr<IGPSSatelliteStorage>);

	bool onData(ByteData&);

	void clear();
private:
	std::shared_ptr<IGPSSatelliteStorage> _storage;

	std::shared_ptr<IDataProcessor> _satClockProcessor;
	std::shared_ptr<IDataProcessor> _ephemerisProcessor;
};