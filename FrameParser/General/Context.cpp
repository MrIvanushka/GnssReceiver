#include "Context.h"

#include "Log.h"

GPSContext::GPSContext()
{
	_storages = std::vector<std::shared_ptr<ISatelliteStorage>>(32);

	for (auto i = 0u; i < _storages.size(); ++i)
		_storages[i] = std::make_shared<GPSSatelliteStorage>();
}

std::shared_ptr<ISatelliteStorage> GPSContext::storage(PRN prn)
{
	if (prn >= _storages.size())
	{
		LOG_ERROR("Unavailable Satellite PRN=", prn);
		return nullptr;
	}

	return _storages[prn];
}