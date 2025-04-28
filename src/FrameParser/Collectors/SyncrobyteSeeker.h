#pragma once

#include <cstdint>

namespace gnssRecv
{
namespace frameParser
{

	class SyncrobyteSeeker
	{
	public:
		bool reachedSyncronization(uint8_t bit);

		void clear();

		uint8_t preamble() const { return _preamble; }

		bool flipped() const { return _flipped; }

		uint8_t d29() const { return _d29; }
		uint8_t d30() const { return _d30; }
	private:
		const uint8_t _preamble = 0b10001011;
		const uint8_t _flippedPreamble = 0b01110100;

		bool _flipped = false;
		uint8_t _lastByte = 0;
		uint8_t _d29;
		uint8_t _d30;
	};

} //namespace frameParser

} //namespace gnssRecv