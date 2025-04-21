#pragma once

#include "IDataProcessor.h"
#include "IGPSSatelliteStorage.h"
#include "Utility.h"
#include <memory>

namespace gnssRecv
{
namespace frameParser
{

class SubframeProcessor
{
public:
	SubframeProcessor(std::shared_ptr<IGPSSatelliteStorage>);

	bool onData(ByteData&);

	void clear();

	const Stat& stat() const { return _stat; }
private:
	std::shared_ptr<IGPSSatelliteStorage> _storage;

	std::shared_ptr<IDataProcessor> _satClockProcessor;
	std::shared_ptr<IDataProcessor> _ephemerisProcessor;

	Stat _stat;
};

} //namespace frameParser

} //namespace gnssRecv