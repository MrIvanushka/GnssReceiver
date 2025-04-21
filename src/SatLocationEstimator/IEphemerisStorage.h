#pragma once

#include "ProtocolType.h"

namespace gnssRecv
{
namespace satLocationEstimator
{

class IEphemerisStorage
{
public:
	virtual ~IEphemerisStorage() = default;

	virtual ProtocolType type() const = 0;
};

} //namespace satLocationEstimator

} //namespace gnssRecv