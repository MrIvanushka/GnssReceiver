#include "GnssStorage.h"

#include "Log.h"
#include "GPSSatStorage.h"

using namespace gnssRecv;

GnssStorage::GnssStorage(ProtocolType protocolType) :
	_protocolType(protocolType)
{}

std::shared_ptr<ISatStorage> GnssStorage::getSatStorage(PRN prn)
{
	auto satIt = _satStorages.find(prn);
	if (satIt != _satStorages.end())
		return satIt->second;

	return makeSatStorage(prn);
}

std::shared_ptr<const ISatStorage> GnssStorage::getSatStorage(PRN prn) const
{
	auto satIt = _satStorages.find(prn);
	if (satIt != _satStorages.end())
		return satIt->second;

	return nullptr;
}

std::shared_ptr<ISatStorage> GnssStorage::makeSatStorage(PRN prn)
{
	std::shared_ptr<ISatStorage> newStorage = nullptr;

	switch (_protocolType)
	{
	case ProtocolType::GPS:
		newStorage = std::make_shared<GPSSatStorage>();
		break;
	case ProtocolType::Glonass:
		LOG_ERROR("GLONASS is not supported");
		return nullptr;
	case ProtocolType::Galileo:
		LOG_ERROR("Galileo is not supported");
		return nullptr;
	case ProtocolType::BeiDou:
		LOG_ERROR("BeiDou is not supported");
		return nullptr;
	default:
		LOG_ERROR("Unknown protocol type");
		return nullptr;
	}
	_satStorages[prn] = newStorage;
	_availableSatellites.push_back(prn);
	return newStorage;
}