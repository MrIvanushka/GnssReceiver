#pragma once

#include "IFrameParser.h"
#include "Context.h"

#include "BitCollector.h"
#include "SubframeCollector.h"
#include "SubframeProcessor.h"

class GPSFrameParser : public IFrameParser
{
private:
	class SatelliteDataParser
	{
	public:
		SatelliteDataParser(std::shared_ptr<GPSSatelliteStorage>);

		void handleSignal(double signal);
	private:
		BitCollector		_bitCollector;
		SubframeCollector	_subframeCollector;
		SubframeProcessor	_subframeProcessor;
	};
public:
	GPSFrameParser(std::shared_ptr<IContext>);
public:
	void handleSignal(double signal, PRN prn) override;

	void clear() override;

	std::vector<Stat> stat() const override;
private:
	std::shared_ptr<IContext> _context;

	std::unordered_map<PRN, std::shared_ptr<SatelliteDataParser>> _parsers;
};