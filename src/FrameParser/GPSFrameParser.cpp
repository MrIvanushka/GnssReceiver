#include "GPSFrameParser.h"

using namespace gnssRecv::frameParser;

GPSFrameParser::GPSFrameParser(std::shared_ptr<IGPSSatelliteStorage> storage) :
	_subframeProcessor(storage)
{
}

void GPSFrameParser::handleSignal(double signal)
{
	_bitCollector.collectSignal(signal);
	auto bits = _bitCollector.getBitSequence();
	ByteData subframe;
	for (auto bit : bits)
	{
		if (_subframeCollector.makeSubframe(bit, &subframe))
			_subframeProcessor.onData(subframe);

		subframe.clear();
	}
}

void GPSFrameParser::clear()
{
	_bitCollector.clear();
	_subframeCollector.clear();
	_subframeProcessor.clear();
}

std::vector<Stat> GPSFrameParser::stat() const
{
	return { _bitCollector.stat(), _subframeCollector.stat(), _subframeProcessor.stat() };
}