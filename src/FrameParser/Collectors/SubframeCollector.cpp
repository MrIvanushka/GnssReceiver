#include "SubframeCollector.h"

using namespace gnssRecv::frameParser;

typedef FrameParserStatNames::FrameParserStatKey UsedStatKey;

SubframeCollector::SubframeCollector()
{
	auto& statNames = FrameParserStatNames::names;

	std::unordered_map<StatKey, std::string> usedNames =
	{
		{ UsedStatKey::ReceivedBits, statNames[UsedStatKey::ReceivedBits] },
		{ UsedStatKey::ProducedWords, statNames[UsedStatKey::ProducedWords] },
		{ UsedStatKey::ProducedSubframes, statNames[UsedStatKey::ProducedSubframes] },
		{ UsedStatKey::TlmSyncronizationErrors, statNames[UsedStatKey::TlmSyncronizationErrors] },
		{ UsedStatKey::ParityErrors, statNames[UsedStatKey::ParityErrors] }
	};

	_stat = Stat(statNames[UsedStatKey::SubframeCollectorStat], usedNames);
}

bool SubframeCollector::makeSubframe(uint8_t bit, ByteData* ret)
{
	_stat.increment(UsedStatKey::ReceivedBits);
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
			_stat.increment(UsedStatKey::ProducedSubframes);
			_buildingSubframe.removeLeft(_wordSize); //cut TLM
			*ret = _buildingSubframe;
			_buildingSubframe.clear();
			return true;
		}
		return false;
	}
	return false;
}

void SubframeCollector::clear()
{
	_currentState = OFF;
	_syncronizer.clear();
	_wordCollector.clear();
	_buildingSubframe.clear();
	_stat.clear();
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
		_stat.increment(UsedStatKey::ProducedWords);
		if (_buildingSubframe.size() == 0 && word.cdata()[0] != _syncronizer.preamble() && word.cdata()[0] != (~_syncronizer.preamble()))
		{
			_stat.increment(UsedStatKey::TlmSyncronizationErrors);
			_currentState = OFF;
			LOG_WARN("New subframe preamble is missed");
		}
		_buildingSubframe.append(word);
		break;
	case WordCollector::StillCollecting:
		break;
	case WordCollector::ParityError:
		_stat.increment(UsedStatKey::ProducedWords);
		_stat.increment(UsedStatKey::ParityErrors);
		_currentState = OFF;
		LOG_WARN("Word parity validation error happened");
		break;
	}
}