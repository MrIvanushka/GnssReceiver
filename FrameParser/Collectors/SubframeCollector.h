#pragma once

#include "WordCollector.h"
#include "SyncrobyteSeeker.h"

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
	bool makeSubframe(uint8_t bit, ByteData* ret);

	State state() const { return _currentState; }
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
};