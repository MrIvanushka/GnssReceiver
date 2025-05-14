#pragma once

#include "IGPSSatStorage.h"
#include "IGPSSatelliteStorage.h"

namespace gnssRecv
{

class GPSFrameParserStorageWrapper : public frameParser::IGPSSatelliteStorage
{
public:
	GPSFrameParserStorageWrapper(std::shared_ptr<IGPSSatStorage>);

	void setZCounter(uint32_t value) override;
	void setSatelliteClock(const frameParser::SatClockHeader&) override;
	void setEphemeris(const frameParser::EphemerisHeader&) override;
private:
	std::shared_ptr<IGPSSatStorage> _storage;
};

} //namespace gnssRecv