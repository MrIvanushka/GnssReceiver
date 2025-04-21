#pragma once

#include "WordCollector.h"
#include "SyncrobyteSeeker.h"
#include "Utility.h"

namespace gnssRecv
{
namespace frameParser
{

class SubframeCollector
{
public:
	enum State
	{
		OFF,
		SYNCRONIZING,
		OPERATION
	};
public:
	SubframeCollector();

	bool makeSubframe(uint8_t bit, ByteData* ret);

	void clear();

	State state() const { return _currentState; }

	const Stat& stat() const { return _stat; }
private:
	void doSyncronization(uint8_t bit);

	void doOperation(uint8_t bit);
private:
	const uint8_t _subframePayloadSizeBytes = 30;
	const uint8_t _wordSize = 3;

	ByteData _buildingSubframe;

	SyncrobyteSeeker _syncronizer;
	WordCollector _wordCollector;

	State _currentState = State::OFF;

	Stat _stat;
};

} //namespace frameParser

} //namespace gnssRecv