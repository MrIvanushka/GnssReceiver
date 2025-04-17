#include "SubframeCollector.h"

#include "Log.h"

bool SubframeCollector::makeSubframe(uint8_t bit, ByteData* ret)
{
	switch (_currentState)
	{
	case OFF:
		_currentState = SYNCRONIZING;
		LOG_INFO("Subframe collector is now SYNCRONIZING");
		_buildingSubframe.clear();
		_syncronizer.clear();
	case SYNCRONIZING:
		doSyncronization(bit);
		return false;
	case OPERATION:
		doOperation(bit);
		if (_buildingSubframe.size() >= _subframePayloadSizeBytes)
		{
			_buildingSubframe.removeLeft(_wordSize); //cut TLM
			*ret = _buildingSubframe;
			_buildingSubframe.clear();
			return true;
		}
		return false;
	}
	return false;
}

void SubframeCollector::doSyncronization(uint8_t bit)
{
	if (_syncronizer.reachedSyncronization(bit))
	{
		_currentState = OPERATION;
		_wordCollector.clear();
		_wordCollector.mentionBytes(ByteData(_syncronizer.preamble(), 1));
		LOG_INFO("Subframe collector is now OPERATION");
	}
}

void SubframeCollector::doOperation(uint8_t bit)
{
	ByteData word;
	switch (_wordCollector.collectBit(bit, &word))
	{
	case WordCollector::Ok:
		if (_buildingSubframe.size() == 0 && word.cdata()[0] != _syncronizer.preamble() && word.cdata()[0] != (~_syncronizer.preamble()))
		{
			_currentState = OFF;
			LOG_WARN("New subframe preamble is missed");
		}
		_buildingSubframe.append(word);
		break;
	case WordCollector::StillCollecting:
		break;
	case WordCollector::ParityError:
		_currentState = OFF;
		LOG_WARN("Word parity validation error happened");
		break;
	}
}