#pragma once

#include "IDataProcessor.h"
#include "IGPSSatelliteStorage.h"

namespace gnssRecv
{
namespace frameParser
{

class EphemerisProcessor : public IDataProcessor
{
public:
	EphemerisProcessor(std::shared_ptr<IGPSSatelliteStorage>);

	bool onData(ByteData&, SubframeType) override;

	void clear() override;
private:
	bool collectFirstFragment(ByteData&);

	bool collectSecondFragment(ByteData&);
private:
	ByteData _collectedData;

	std::shared_ptr<IGPSSatelliteStorage> _storage;
};

} //namespace frameParser

} //namespace gnssRecv