#pragma once

#include "Utility.h"

namespace gnssRecv
{
namespace frameParser
{

PROTO_ALIGN_BEGIN
struct SatClockHeader
{
public:
	uint16_t	weekNumber() const { return R16(_wnAndUra) >> 6; }
	uint8_t		uraIndex() const { return R16(_wnAndUra) & 0b0000'1111; }
	uint8_t		svHealth() const { return _svHealth >> 2; }
	bool		l2pDataFlag() const { return _reservedBytes[0] & 0b1000'0000; }
	double		tGD() const { return _tGD * pow(2, (- 31)); }
	uint16_t	iodc() const { return (_svHealth & 0x03) * 0x01'00 + _iodcLast; }
	uint64_t	tOC() const { return R16(_tOC) * 16; }
	long double	af2() const { return toSigned8(_af2) * pow(2, (-55)); }
	double		af1() const { return toSigned16(R16(_af1)) * pow(2, (-43)); }
	double		af0() const { return (toSigned22(_af0[0] * 0x01'00'00 + _af0[1] * 0x01'00 + _af0[2]) >> 2) * pow(2, (-31)); }
private:
	int32_t		toSigned16(uint16_t u) const { return (u & 0x7F'FF) - (u & 0x80'00); }
	int16_t		toSigned8(uint8_t u) const { return (u & 0x7F) - (u & 0x80); }
	int32_t		toSigned22(uint32_t u) const { return (u & 0x1F'FF'FF) - (u & 0x20'00'00); }
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

} //namespace frameParser

} //namespace gnssRecv