#include "GPSSatStorage.h"

#include "Log.h"

using namespace gnssRecv;

TrackingState GPSSatStorage::trackingState() const
{
	return _currentState;
}

math::Vector3 GPSSatStorage::location() const
{
	return _location;
}

double GPSSatStorage::satelliteTimeOfWeek() const
{
	static const uint32_t subframeDurationSec = 6;
	double millisecPart = _millisecondsAfterLastHow;
	auto zCounterFactor = _zCounter * subframeDurationSec;
	return correctTime(zCounterFactor + millisecPart / 1000);
}

double GPSSatStorage::interpolatedTime(double localTime) const
{
	auto sigDuration = _lastTimestamp - _previousTimestamp;
	auto lerpFactor = (localTime * 1000 - _lastTimestamp) / sigDuration;
	static const uint32_t subframeDurationSec = 6;
	double millisecPart = (_millisecondsAfterLastHow + lerpFactor) / 1000;
	auto zCounterFactor = _zCounter * subframeDurationSec;

	return correctTime(zCounterFactor + millisecPart);
}

double GPSSatStorage::lastReceiveLocalTime() const
{
	return _lastTimestamp / 1000;
}

uint64_t GPSSatStorage::secondsUTC() const
{
	static const uint32_t subframeDurationSec = 6;
	auto zCounterFactor = _zCounter * subframeDurationSec;
	auto subframePartFactor = _millisecondsAfterLastHow / 1000;
	auto weekFactor = (_lastSatClock.weekNumber() + 2048) * 604'800ull;
	auto epochShift = 315964800ull;
	auto gpsUtcOffset = 18;
	auto gpsTime = weekFactor + zCounterFactor + subframePartFactor;
	return gpsTime + epochShift - gpsUtcOffset;
}

void GPSSatStorage::updateLocation(const math::Vector3& newLocation)
{
	_location = newLocation;
}

void GPSSatStorage::handleSyncroError()
{
	if (_currentState == TrackingState::LOST)
		LOG_ERROR("Receiving stat from lost station!");

	_currentState = TrackingState::SYNCRONIZING;
}

void GPSSatStorage::handleSyncroSuccess()
{
	if (_currentState == TrackingState::LOST)
		LOG_ERROR("Receiving stat from lost station!");

	_currentState = TrackingState::COLLECTING_DATA;
}

void GPSSatStorage::handleNewSignalHappened(double timestamp)
{
	if (_currentState == TrackingState::LOST)
		_currentState = TrackingState::SYNCRONIZING;

	++_millisecondsAfterLastHow;
	_previousTimestamp = _lastTimestamp;
	_lastTimestamp = timestamp;
}

void GPSSatStorage::handleMissedSignal()
{
	_currentState = TrackingState::LOST;
	_hasHow = false;
	_hasSatClock = false;
	_hasEphemeris = false;
}

void GPSSatStorage::setZCounter(uint32_t zCounter)
{
	_zCounter = zCounter;
	_hasHow = true;
	tryUpdateState();
	_millisecondsAfterLastHow = 0;
	_timestampAtLastHow = _lastTimestamp;
}

void GPSSatStorage::setSatClock(const frameParser::SatClockHeader& msg)
{
	_lastSatClock = msg;
	_hasSatClock = true;
	tryUpdateState();
}

void GPSSatStorage::setEphemeris(const frameParser::EphemerisHeader& msg)
{
	_lastEphemeris = msg;
	_hasEphemeris = true;
	tryUpdateState();
}

uint32_t GPSSatStorage::zCounter() const
{
	return _zCounter;
}

const frameParser::SatClockHeader& GPSSatStorage::lastSatClock() const
{
	return _lastSatClock;
}

const frameParser::EphemerisHeader& GPSSatStorage::lastEphemeris() const
{
	return _lastEphemeris;
}

double GPSSatStorage::correctTime(double time) const
{
	auto dt = time - _lastSatClock.tOC();
	double f = -4.442807633e-10;
	double dtr = f * _lastEphemeris.e() * _lastEphemeris.sqrtOfA() * sin(_eccentricAnomaly);
	double dtsv = _lastSatClock.af0() + _lastSatClock.af1() * dt + _lastSatClock.af2() * dt * dt + dtr;
	return time + dtsv - _lastSatClock.tGD();
}

void GPSSatStorage::tryUpdateState()
{
	if (_currentState == TrackingState::COLLECTING_DATA && _hasHow && _hasSatClock && _hasEphemeris)
		_currentState = TrackingState::ACTIVE;
}