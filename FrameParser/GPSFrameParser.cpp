#include "GPSFrameParser.h"

GPSFrameParser::SatelliteDataParser::SatelliteDataParser(std::shared_ptr<GPSSatelliteStorage> storage) :
	_subframeProcessor(storage)
{
}

void GPSFrameParser::SatelliteDataParser::handleSignal(double signal)
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

GPSFrameParser::GPSFrameParser(std::shared_ptr<IContext> context) : _context(context)
{}

void GPSFrameParser::handleSignal(double signal, PRN prn)
{
	auto parserIt = _parsers.find(prn);

	if (parserIt == _parsers.end())
	{
		LOG_INFO("Data from PRN=", prn, " detected");
		auto newStorage = std::dynamic_pointer_cast<GPSSatelliteStorage>(_context->storage(prn));
		if (!newStorage)
		{
			LOG_ERROR("Satellite storage for PRN=", prn, " has no GPS format!");
			return;
		}
		_parsers[prn] = std::make_shared<SatelliteDataParser>(newStorage);
		_parsers[prn]->handleSignal(signal);
		return;
	}
	parserIt->second->handleSignal(signal);
}

void GPSFrameParser::clear()
{
	_parsers.clear();
}

std::vector<Stat> GPSFrameParser::stat() const
{
	return {};
}