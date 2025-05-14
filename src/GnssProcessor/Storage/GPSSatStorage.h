#pragma once

#include "IGPSSatStorage.h"
#include "ISatLocationEstimator.h"
#include "IFrameParser.h"

namespace gnssRecv
{

class GPSSatStorage : public IGPSSatStorage
{
public:
	TrackingState trackingState() const override;

	math::Vector3 location() const override;

	double satelliteTimeOfWeek() const override;

	double interpolatedTime(double localTime) const override;

	uint64_t secondsUTC() const override;

	double lastReceiveLocalTime() const override;

	void handleSyncroError() override;

	void handleSyncroSuccess() override;

	void updateLocation(const math::Vector3& newLocation) override;

	void updateCodeShift(double codeshift) override;

	void handleNewSignalHappened(double timestamp) override;

	void handleMissedSignal() override;

	void setZCounter(uint32_t) override;

	void setSatClock(const frameParser::SatClockHeader&) override;

	void setEphemeris(const frameParser::EphemerisHeader&) override;

	void setEccentricAnomaly(double value) override { _eccentricAnomaly = value; }

	uint32_t zCounter() const override;

	const frameParser::SatClockHeader& lastSatClock() const override;

	const frameParser::EphemerisHeader& lastEphemeris() const override;
private:
	double correctTime(double time) const;

	void tryUpdateState();
private:
	TrackingState _currentState = TrackingState::COLLECTING_DATA;

	math::Vector3 _location;
	uint32_t _millisecondsAfterLastHow;
	double _lastTimestamp;
	double _previousTimestamp;
	double _timestampAtLastHow;
	double _eccentricAnomaly;
	
	bool _hasHow = false;
	bool _hasSatClock = false;
	bool _hasEphemeris = false;

	uint32_t _zCounter = 0;
	frameParser::SatClockHeader _lastSatClock;
	frameParser::EphemerisHeader _lastEphemeris;
};


} //namespace gnssRecv