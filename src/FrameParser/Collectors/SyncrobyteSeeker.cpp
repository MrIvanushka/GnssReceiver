#include "SyncrobyteSeeker.h"

using namespace gnssRecv::frameParser;

bool SyncrobyteSeeker::reachedSyncronization(uint8_t bit)
{
	_d29 = _d30;
	_d30 = (_lastByte & 0b1000'0000) ? 1 : 0;

	_lastByte <<= 1;
	if (bit)
		_lastByte += 1;

	if (_lastByte == _preamble)
	{
		_flipped = false;
		return true;
	}
	else if (_lastByte == _flippedPreamble)
	{
		_flipped = true;
		return true;
	}
	return false;
}

void SyncrobyteSeeker::clear()
{
	_lastByte = 0;
}