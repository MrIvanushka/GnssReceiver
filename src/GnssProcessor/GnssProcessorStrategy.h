#pragma once

#include "IGnssProcessorStrategy.h"

#include <unordered_set>

#include "SatTracker.h"
#include "IReceiverLocationEstimator.h"

namespace gnssRecv
{

class GnssProcessorStrategy : public IGnssProcessorStrategy
{
private:
	typedef int PRN;
	typedef receiverLocationEstimator::IReceiverLocationEstimator IRecvLocEst;
public:
	GnssProcessorStrategy(std::shared_ptr<IGnssStorage>);

	void receiveSignal(double signal, double timestamp, int PRN) override;

	void updateReceiverLocation() override;

	void clear() override;

	std::shared_ptr<const IGnssStorage> storage() const override;

	std::vector<Stat> satelliteStat(int PRN) const override;
private:
	math::Vector3 ecefToGeodetic(math::Vector3 ecef);
private:
	double _receiverTime = 0;

	std::shared_ptr<IGnssStorage> _storage;

	std::unordered_set<PRN> _prnsAfterLastLocationRecalc;

	std::unordered_map<PRN, SatTracker> _satTrackers;

	std::unique_ptr<IRecvLocEst> _receiverLocationEstimator;
};

} //namespace gnssRecv