#pragma once

#include "ProtocolType.h"

class IEphemerisStorage
{
public:
	virtual ~IEphemerisStorage() = default;

	virtual ProtocolType type() const = 0;
};