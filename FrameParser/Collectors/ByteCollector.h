#pragma once

#include <cstdint>
#include <vector>

class ByteCollector
{
public:
	bool makeByte(uint8_t bit, uint8_t* ret);

	void clear();
private:
	uint8_t _buildingByte = 0;
	uint8_t _filledBitsCount = 0;
};