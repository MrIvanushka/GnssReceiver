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

	if (((signal > 0 && _lastSignalSum < 0) || (signal < 0 && _lastSignalSum > 0)) && (abs(signal) * 1.5) > (abs(_lastSignalSum) / _lastCrossTime))
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
	_currentStage = Stage::NO_SYNC;
	_crossErrors = 0;
	_sameBitGiven = 0;
}

void BitCollector::handleNewBit()
{
	if (_gaveSequence)
	{
		_gaveSequence = false;
		_builtBits.clear();
	}

	if (_lastCrossTime >= _signalsCountInBit || (_currentStage == Stage::SYNC_FULL && _lastCrossTime >= _signalsCountInBit - (2 + _sameBitGiven)))
	{
		auto mean = _lastSignalSum / _signalsCountInBit;
		auto currentBit = 0;
		if (mean > 0)
		{
			_builtBits.push_back(0);
		}
		else
		{
			_builtBits.push_back(1);
			currentBit = 1;
		}
		if (currentBit == _lastBit)
		{
			_sameBitGiven += 1;
		}
		else
		{
			_sameBitGiven = 0;
		}
		_lastBit = currentBit;

		++_filledBitsCount;
		_stat.increment(UsedStatKey::CollectedBits);

		if (_currentStage == Stage::SYNC_RAW)
			_currentStage = Stage::SYNC_FULL;
		else if (_currentStage == Stage::NO_SYNC)
			_currentStage = Stage::SYNC_RAW;
	}
	else if (_currentStage == Stage::SYNC_FULL)
	{
		_crossErrors += 1;

		if(_crossErrors < _signalsCountInBit / 1.5)
			return;

		_currentStage == Stage::NO_SYNC;
		_stat.increment(UsedStatKey::BitErrors);
		LOG_WARN("Signal is crossed too early; distance = ", (uint32_t)_lastCrossTime);
	}
	
	_lastSignalSum = 0;
	_lastCrossTime = 0;
	_crossErrors = 0;
}