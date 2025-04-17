#pragma once

#include "IDataProcessor.h"
#include "Context.h"
#include <memory>

class SubframeProcessor
{
public:
	SubframeProcessor(std::shared_ptr<GPSSatelliteStorage>);

	bool onData(ByteData&);
private:
	std::shared_ptr<GPSSatelliteStorage> _storage;

	std::shared_ptr<IDataProcessor> _satClockProcessor;
	std::shared_ptr<IDataProcessor> _ephemerisProcessor;
};