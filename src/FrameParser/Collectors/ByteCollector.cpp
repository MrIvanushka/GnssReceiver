#include "ByteCollector.h"

using namespace gnssRecv::frameParser;

bool ByteCollector::makeByte(uint8_t bit, uint8_t* ret)
{
	if (_filledBitsCount == 8)
		clear();

	if (bit)
		_buildingByte += 1 << (7 - _filledBitsCount);

	++_filledBitsCount;
	if (_filledBitsCount == 8)
	{
		*ret = _buildingByte;
		return true;
	}
	return false;
}

void ByteCollector::clear()
{
	_filledBitsCount = 0;
	_buildingByte = 0;
}