#include "BitCollector.h"

using namespace gnssRecv::frameParser;

typedef FrameParserStatNames::FrameParserStatKey UsedStatKey;

BitCollector::BitCollector()
{
	auto& statNames = FrameParserStatNames::names;

	std::unordered_map<StatKey, std::string> usedNames =
	{
		{ UsedStatKey::ReceivedSignals, statNames[UsedStatKey::ReceivedSignals] },
		{ UsedStatKey::CollectedBits, statNames[UsedStatKey::CollectedBits] },
		{ UsedStatKey::BitErrors, statNames[UsedStatKey::BitErrors] }
	};

	_stat = Stat(statNames[UsedStatKey::BitCollectorStat], usedNames);
}

void BitCollector::collectSignal(double signal)
{
	_stat.increment(UsedStatKey::ReceivedSignals);

	if ((signal > 0 && _lastSignalSum < 0) || (signal < 0 && _lastSignalSum > 0))
		handleNewBit();
	else if (_lastCrossTime == _signalsCountInBit)
		handleNewBit();

	_lastSignalSum += signal;
	++_lastCrossTime;
}

std::vector<uint8_t> BitCollector::getBitSequence()
{
	if (_gaveSequence)
		return {};

	_gaveSequence = true;
	return _builtBits;
}

void BitCollector::clear()
{
	_gaveSequence = false;
	_builtBits.clear();
	_stat.clear();
}

void BitCollector::handleNewBit()
{
	if (_gaveSequence)
	{
		_gaveSequence = false;
		_builtBits.clear();
	}

	if (_lastCrossTime >= _signalsCountInBit)
	{
		auto mean = _lastSignalSum / 20;
		if (mean > 0)
			_builtBits.push_back(0);
		else
			_builtBits.push_back(1);

		++_filledBitsCount;
		_stat.increment(UsedStatKey::CollectedBits);
	}
	else
	{
		_stat.increment(UsedStatKey::BitErrors);
		LOG_WARN("Signal is crossed too early; distance = ", (uint32_t)_lastCrossTime);
	}
	_lastSignalSum = 0;
	_lastCrossTime = 0;
}