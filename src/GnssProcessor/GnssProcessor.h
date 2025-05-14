#pragma once

#include <thread>

#include "IGnssProcessor.h"
#include "IGnssProcessorStrategy.h"

namespace gnssRecv
{

class GnssProcessor : public IGnssProcessor
{
public:
	void start(ProtocolType, std::shared_ptr<IDataInput>) override;

	void stop() override;

	bool running() const override;

	std::shared_ptr<const IGnssStorage> storage() const override;

	std::vector<Stat> satelliteStat(int PRN) const override;
private:
	void run();

	bool _running = false;
	std::thread _runningThread;

	std::shared_ptr<IDataInput> _dataInput = nullptr;
	std::unique_ptr<IGnssProcessorStrategy> _strategy = nullptr;
};

} //namespace gnssRecv