#include "SyncrobyteSeeker.h"

using namespace gnssRecv::frameParser;

bool SyncrobyteSeeker::reachedSyncronization(uint8_t bit)
{
	_lastByte <<= 1;
	if (bit)
		_lastByte += 1;

	return _lastByte == _preamble || _lastByte == ~_preamble;
}

void SyncrobyteSeeker::clear()
{
	_lastByte = 0;
}