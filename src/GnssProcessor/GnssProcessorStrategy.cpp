#include "GnssProcessorStrategy.h"

#include "SatTrackerFactory.h"
#include "ReceiverLocationEstimatorFactory.h"
#include "RecvEstStorageWrapper.h"

using namespace gnssRecv;

GnssProcessorStrategy::GnssProcessorStrategy(std::shared_ptr<IGnssStorage> storage) :
	_storage(storage)
{
	auto recvWrapper = std::make_shared<RecvEstStorageWrapper>(_storage);
	_receiverLocationEstimator = receiverLocationEstimator::ReceiverLocationEstimatorFactory::makeEstimator(recvWrapper);
}

void GnssProcessorStrategy::receiveSignal(double signal, double timestamp, int PRN)
{
	auto trackerIt = _satTrackers.find(PRN);
	_storage->getSatStorage(PRN)->handleNewSignalHappened(timestamp);

	if (trackerIt == _satTrackers.end())
	{
		auto newSatTracker = SatTrackerFactory::build(_storage->getSatStorage(PRN));
		if (newSatTracker.frameParser == nullptr || newSatTracker.locationEstimator == nullptr)
			return;
		newSatTracker.frameParser->handleSignal(signal);
		_satTrackers[PRN] = newSatTracker;
		return;
	}
	trackerIt->second.frameParser->handleSignal(signal);

	if (_prnsAfterLastLocationRecalc.contains(PRN))
	{
		_prnsAfterLastLocationRecalc.clear();
		updateReceiverLocation();
	}
	_prnsAfterLastLocationRecalc.insert(PRN);
}

void GnssProcessorStrategy::updateReceiverLocation()
{
	double maxLocalTime = 0;
	for (auto prn : _storage->availableSatellites())
	{
		auto satStorage = _storage->getSatStorage(prn);
		auto thisLocalTime = satStorage->lastReceiveLocalTime();
		if (thisLocalTime > maxLocalTime)
			maxLocalTime = thisLocalTime;
	}
	for (auto prn : _storage->availableSatellites())
	{
		if (_storage->getSatStorage(prn)->trackingState() == TrackingState::ACTIVE)
			_storage->getSatStorage(prn)->updateLocation(_satTrackers[prn].locationEstimator->calculateLocation(maxLocalTime));
	}

	auto [recvLocation, recvTime] = _receiverLocationEstimator->calculateLocation(maxLocalTime);
	if (recvLocation.magnitude() > 1)
	{
		auto geodeticLoc = ecefToGeodetic(recvLocation);
		_storage->updateReceiverLocation(geodeticLoc);
	}
}

void GnssProcessorStrategy::clear()
{
	//TODO: clear storage
	_satTrackers.clear();
}

std::shared_ptr<const IGnssStorage> GnssProcessorStrategy::storage() const
{
	return _storage;
}

std::vector<Stat> GnssProcessorStrategy::satelliteStat(int PRN) const
{
	auto trackerIt = _satTrackers.find(PRN);
	if (trackerIt == _satTrackers.end())
		return {};
	return trackerIt->second.frameParser->stat();
}

math::Vector3 GnssProcessorStrategy::ecefToGeodetic(math::Vector3 ecef)
{
	double x = ecef.x;
	double y = ecef.y;
	double z = ecef.z;

	// ── параметры WGS-84 (через constexpr, чтобы вычислялись на этапе компиляции)
	constexpr double a = 6378137.0;               // большая полуось,      м
	constexpr double f = 1.0 / 298.257223563;     // сжатие
	constexpr double e2 = f * (2.0 - f);           // эксцентричность
	constexpr double pi = 3.14159265358979323846;

	// ── долгота ────────────────────────────────────────────────────────
	const double lon = std::atan2(y, x);

	// ── расстояние до оси вращения и начальное приближение широты ─────
	const double p = std::hypot(x, y);           
	double       lat = std::atan2(z, p * (1.0 - e2));

	// ── итерация Боуинга: обычно хватает 2–3 циклов ───────────────────
	for (int k = 0; k < 6; ++k)
	{
		const double sinLat = std::sin(lat);
		const double N = a / std::sqrt(1.0 - e2 * sinLat * sinLat); // радиус кривизны
		const double h = p / std::cos(lat) - N;

		const double prev = lat;
		lat = std::atan2(z, p * (1.0 - e2 * N / (N + h)));

		if (std::fabs(lat - prev) < 1e-12 || k == 5) // ~= 1e-7″
			return math::Vector3(lat / pi * 180, lon / pi * 180, h);
	}
	return math::Vector3(0,0,0);
}