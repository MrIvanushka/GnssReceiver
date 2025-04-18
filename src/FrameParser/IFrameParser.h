#pragma once

#include "Utility.h"

class IFrameParser
{
public:
	virtual ~IFrameParser() = default;

	virtual void handleSignal(double signal) = 0;

	virtual void clear() = 0;

	virtual std::vector<Stat> stat() const = 0;
};