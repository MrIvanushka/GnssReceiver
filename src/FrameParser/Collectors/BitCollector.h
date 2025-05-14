#pragma once

#include "Utility.h"
#include <vector>

namespace gnssRecv
{
namespace frameParser
{

class BitCollector
{
private:
	enum class Stage
	{
		NO_SYNC,
		SYNC_RAW,
		SYNC_FULL
	};
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
	uint8_t _crossErrors = 0;
	uint8_t _lastBit = 0;
	uint8_t _sameBitGiven = 0;

	Stat _stat;

	Stage _currentStage = Stage::NO_SYNC;
};

} //namespace frameParser

} //namespace gnsRecv