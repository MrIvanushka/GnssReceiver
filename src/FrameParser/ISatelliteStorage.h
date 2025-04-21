#pragma once

#include "ProtocolType.h"

namespace gnssRecv
{
namespace frameParser
{

class ISatelliteStorage
{
public:
	virtual ~ISatelliteStorage() = default;
	
	virtual ProtocolType type() const = 0;
};

} //namespace frameParser

} //namespace gnssRecv