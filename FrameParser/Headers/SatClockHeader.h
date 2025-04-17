#pragma once

#include "Utility.h"

PROTO_ALIGN_BEGIN
struct SatClockHeader
{
public:
	uint16_t	weekNumber() const { return R16(_wnAndUra) >> 6; }
	uint8_t		uraIndex() const { return R16(_wnAndUra) & 0b0000'1111; }
	uint8_t		svHealth() const { return _svHealth >> 2; }
	bool		l2pDataFlag() const { return _reservedBytes[0] & 0b1000'0000; }
	uint8_t		tGD() const { return _tGD; }
	uint16_t	iodc() const { return (_svHealth & 0x03) * 0x01'00 + _iodcLast; }
	uint16_t	tOC() const { return R16(_tOC); }
	uint8_t		af2() const { return _af2; }
	uint16_t	af1() const { return R16(_af1); }
	uint32_t	af0() const { return (_af0[0] * 0x01'00'00 + _af0[1] * 0x01'00 + _af0[2]) >> 2; }
private:
	uint16_t	_wnAndUra;
	uint8_t		_svHealth;
	uint8_t		_reservedBytes[11];
	uint8_t		_tGD;
	uint8_t		_iodcLast;
	uint16_t	_tOC;
	uint8_t		_af2;
	uint16_t	_af1;
	uint8_t		_af0[3];
};
PROTO_ALIGN_END