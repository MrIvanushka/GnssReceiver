#pragma once

#include "Utility.h"

namespace gnssRecv
{
namespace frameParser
{

class IFrameParser
{
public:
	virtual ~IFrameParser() = default;

	virtual void handleSignal(double signal) = 0;

	virtual void clear() = 0;

	virtual uint32_t bitsAfterLastSuperframe() const = 0;

	virtual std::vector<Stat> stat() const = 0;
};

} //namespace frameParser

} //namespace gnssRecv