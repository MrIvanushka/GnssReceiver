#pragma once

#include "Utility.h"

namespace gnssRecv
{
namespace frameParser
{

PROTO_ALIGN_BEGIN
struct EphemerisHeader
{
public:
	uint8_t		iode() const { return _iode1; }
	double		cRS() const { return toSigned16(R16(_cRS)) * pow(2, (-5)); }
	double		deltaN() const { return toSigned16(R16(_deltaN)) * pow(2,(-43)); }
	double		m0() const { return toSigned32(R32(_m0)) * pow(2,(-31)); }
	double		cUC() const { return toSigned16(R16(_cUC)) * pow(2,(-29)); }
	double		e() const { return R32(_e) * pow(2,(-33)); }
	double		cUS() const { return toSigned16(R16(_cUS)) * pow(2,(-29)); }
	double		sqrtOfA() const { return R32(_sqrtOfA) * pow(2,(-19)); }
	double		tOE() const { return R16(_tOE) * pow(2,4); }
	bool		fitInterval() const { return _aodo & 0b1000'0000; }
	uint8_t		aodo() const { return (_aodo >> 2) & 0b0001'1111; }
	double		cIC() const { return toSigned16(R16(_cIC)) * pow(2,(-29)); }
	double		omega0() const { return toSigned32(R32(_omega0)) * pow(2,(-31)); }
	double		cIS() const { return toSigned16(R16(_cIS)) * pow(2,(-29)); }
	double		i0() const { return toSigned32(R32(_i0)) * pow(2,(-31)); }
	double		cRC() const { return toSigned16(R16(_cRC)) * pow(2,(-5)); }
	double		omega() const { return toSigned32(R32(_omega)) * pow(2, (-31)); }
	double		ascendingRate() const { return (_angularSpeed[0] * 0x01'00'00 + _angularSpeed[1] * 0x01'00 + _angularSpeed[2]) * pow(2,(-43)); }
	double		inclinationRate() const { return (toSigned16(R16(_idot)) >> 2) * pow(2, (-43)); }
private:
	int16_t		toSigned16(uint16_t u) const { return (u & 0x7F'FF) - (u & 0x80'00); }
	int32_t		toSigned32(uint32_t u) const { return (u & 0x7F'FF'FF'FF) - (u & 0x80'00'00'00); }
private:
	//======subframe 1======//
	uint8_t		_iode1;
	uint16_t	_cRS;
	uint16_t	_deltaN;
	uint32_t	_m0;
	uint16_t	_cUC;
	uint32_t	_e;
	uint16_t	_cUS;
	uint32_t	_sqrtOfA;
	uint16_t	_tOE;
	uint8_t		_aodo;
	//======subframe 2======//
	uint16_t	_cIC;
	uint32_t	_omega0;
	uint16_t	_cIS;
	uint32_t	_i0;
	uint16_t	_cRC;
	uint32_t	_omega;
	uint8_t		_angularSpeed[3];
	uint8_t		_iode2;
	uint16_t	_idot;
};
PROTO_ALIGN_END

} //namespace frameParser

} //namespace gnssRecv