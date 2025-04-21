#pragma once

#include "IFrameParser.h"
#include "IGPSSatelliteStorage.h"

#include "BitCollector.h"
#include "SubframeCollector.h"
#include "SubframeProcessor.h"

namespace gnssRecv
{
namespace frameParser
{

class GPSFrameParser : public IFrameParser
{
public:
	GPSFrameParser(std::shared_ptr<IGPSSatelliteStorage>);
public:
	void handleSignal(double signal) override;

	void clear() override;

	std::vector<Stat> stat() const override;
private:
	BitCollector		_bitCollector;
	SubframeCollector	_subframeCollector;
	SubframeProcessor	_subframeProcessor;
};

} //namespace frameParser

} //namespace gnssRecv