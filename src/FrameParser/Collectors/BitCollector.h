#pragma once

#include "Utility.h"
#include <vector>

class BitCollector
{
public:
	BitCollector();

	void collectSignal(double signal);

	std::vector<uint8_t> getBitSequence();

	void clear();

	const Stat& stat() const { return _stat; }
private:
	void handleNewBit();
private:
	const uint8_t _signalsCountInBit = 20;

	uint8_t _lastCrossTime = 0;
	bool _gaveSequence = false;
	std::vector<uint8_t> _builtBits;
	uint8_t _buildingByte = 0;
	uint8_t _filledBitsCount = 0;
	double _lastSignalSum = 1;

	Stat _stat;
};