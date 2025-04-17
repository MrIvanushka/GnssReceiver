#include "BitCollector.h"

#include "Log.h"

void BitCollector::collectSignal(double signal)
{
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
}

void BitCollector::handleNewBit()
{
	if (_gaveSequence)
		clear();

	if (_lastCrossTime >= _signalsCountInBit)
	{
		auto mean = _lastSignalSum / 20;
		if (mean > 0)
			_builtBits.push_back(0);
		else
			_builtBits.push_back(1);

		_lastSignalSum = 0;
		++_filledBitsCount;
	}
	else
	{
		LOG_WARN("Signal is crossed too early; distance = ", (uint32_t)_lastCrossTime);
	}
	_lastCrossTime = 0;
}