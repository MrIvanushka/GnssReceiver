#include "GnssProcessor.h"

#include "GnssProcessorStrategyFactory.h"
#include "Log.h"

using namespace gnssRecv;

void GnssProcessor::start(ProtocolType protocol, std::shared_ptr<IDataInput> dataInput)
{
	if (_running)
	{
		LOG_ERROR("GNSS Processor is already running!");
		return;
	}
	_dataInput = dataInput;
	_strategy = GnssProcessorStrategyFactory::makeStrategy(protocol);
	_running = true;
	_runningThread = std::thread(&GnssProcessor::run, this);
}

void GnssProcessor::stop()
{
	if (!_running)
	{
		LOG_ERROR("GNSS Processor is already stopped!");
		return;
	}
	_running = false;
	_runningThread.join();
	_dataInput = nullptr;
}

bool GnssProcessor::running() const
{
	return _running;
}

std::shared_ptr<const IGnssStorage> GnssProcessor::storage() const
{
	return _strategy->storage();
}

std::vector<Stat> GnssProcessor::satelliteStat(int PRN) const
{
	return _strategy->satelliteStat(PRN);
}

void GnssProcessor::run()
{
	double signal;
	double timestamp;
	int PRN;

	while (_running)
	{
		if (_dataInput->getSignal(&signal, &timestamp, &PRN))
		{
			_strategy->receiveSignal(signal, timestamp, PRN);
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::nanoseconds(1));
		}
	}
}