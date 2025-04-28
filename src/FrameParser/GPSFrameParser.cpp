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

	++_bitsAfterLastSuperframe;
	for (auto bit : bits)
	{
		if (_subframeCollector.makeSubframe(bit, &subframe))
		{
			_subframeProcessor.onData(subframe);
			_bitsAfterLastSuperframe = 0;
		}
		subframe.clear();
	}
}

void GPSFrameParser::clear()
{
	_bitCollector.clear();
	_subframeCollector.clear();
	_subframeProcessor.clear();
}

uint32_t GPSFrameParser::bitsAfterLastSuperframe() const
{
	return _bitsAfterLastSuperframe;
}

std::vector<gnssRecv::Stat> GPSFrameParser::stat() const
{
	return { _bitCollector.stat(), _subframeCollector.stat(), _subframeProcessor.stat() };
}