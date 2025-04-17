#pragma once

#include "IDataProcessor.h"
#include "Context.h"

class EphemerisProcessor : public IDataProcessor
{
public:
	EphemerisProcessor(std::shared_ptr<GPSSatelliteStorage>);

	bool onData(ByteData&, SubframeType) override;
private:
	bool collectFirstFragment(ByteData&);

	bool collectSecondFragment(ByteData&);
private:
	ByteData _collectedData;

	std::shared_ptr<GPSSatelliteStorage> _storage;
};