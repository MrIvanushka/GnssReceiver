#pragma once

#include "Utility.h"

namespace gnssRecv
{
namespace frameParser
{

PROTO_ALIGN_BEGIN
struct HandoverWordHeader
{
public:
	uint32_t	zCounter() const { return (static_cast<uint32_t>(_bytes[0]) << 9) + (static_cast<uint32_t>(_bytes[1]) << 1) + (_bytes[2] >> 7); }
	bool		emergency() const { return _bytes[2] & 0b0100'0000; }
	bool		antiSpoof() const { return _bytes[2] & 0b0010'0000; }
	uint8_t		subframeID() const { return (_bytes[2] >> 2) & 0b0000'0111; }
private:
	uint8_t	_bytes[3];
};
PROTO_ALIGN_END

} //namespace frameParser

} //namespace gnssRecv