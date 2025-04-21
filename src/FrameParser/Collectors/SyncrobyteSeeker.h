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
	private:
		const uint8_t _preamble = 0b10001011;

		uint8_t _lastByte = 0;
	};

} //namespace frameParser

} //namespace gnssRecv