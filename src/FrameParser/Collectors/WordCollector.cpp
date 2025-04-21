#include "WordCollector.h"

#include "Log.h"

using namespace gnssRecv::frameParser;

WordCollector::CollectResult WordCollector::ParityValidator::validate(uint8_t bit, ByteData& word)
{
	if (bit)
		_buildingParity += 1 << (5 - _filledBitsCount);

	++_filledBitsCount;
	if (_filledBitsCount == 6)
	{
		if (!checkParity(word))
			return ParityError;
		else
			return Ok;
	}
	else
	{
		return StillCollecting;
	}
}

void WordCollector::ParityValidator::clear()
{
	_buildingParity = 0;
	_filledBitsCount = 0;
}

bool WordCollector::ParityValidator::checkParity(ByteData& word)
{
	if (word.size() != 3)
	{
		LOG_ERROR("Built word has invalid size!");
		return false;
	}
	int byte1 = word.cdata()[0];
	int byte2 = word.cdata()[1];
	int byte3 = word.cdata()[2];
	int data = word.cdata()[0] * 0x01'00'00 + (int)word.cdata()[1] * 0x01'00 + (int)word.cdata()[2];

	//https://programmersought.com/article/47346760708/
	unsigned int i, j, S[6];
	int temp, S_temp, P;
	int GPSX_Flag_Data_Parity;
	unsigned int GPS_H[6] = { 0xEC7CD2,0x763E69,0xBB1F34,0x5D8F9A,0xAEC7CD,0x2DEA27 };
	temp = 0;
	P = 0;
	GPSX_Flag_Data_Parity = 0;

	if (_D30 == 1)
	{
		data = (~data) & 0xFFFFFF;
		word.invert();
	}
	for (i = 0;i < 6;i++)
	{
		S[i] = GPS_H[i] & data;
		S_temp = S[i];
		temp = 0;
		for (j = 0;j < 24;j++)
		{
			temp += S_temp & 1;
			S_temp = S_temp >> 1;
		}
		if (temp % 2 == 0)
			temp = 0;
		else
			temp = 1;
		if ((i == 0) || (i == 2) || (i == 5))
			temp = temp ^ _D29;
		else
			temp = temp ^ _D30;
		P = P | (temp << (5 - i));
	}

	_D29 = (_buildingParity & 0x02) >> 1;
	_D30 = _buildingParity & 0x01;
	return P == _buildingParity;
}

WordCollector::CollectResult WordCollector::collectBit(uint8_t bit, ByteData* ret)
{
	CollectResult answer = StillCollecting;

	switch (_currentStage)
	{
	case CollectingPayload:
		buildPayload(bit);
		break;
	case CollectingParity:
		answer = _parityValidator.validate(bit, _buildindWord);
		if (answer != StillCollecting)
		{
			*ret = _buildindWord;
			_buildindWord.clear();
			_currentStage = CollectingPayload;
		}
		break;
	}

	return answer;
}

void WordCollector::mentionBytes(const ByteData& data)
{
	_buildindWord.append(data);
}

void WordCollector::clear()
{
	_currentStage = CollectingPayload;
	_buildindWord.clear();
	_byteCollector.clear();
	_parityValidator.clear();
}

void WordCollector::buildPayload(uint8_t bit)
{
	uint8_t byte;
	if (!_byteCollector.makeByte(bit, &byte))
		return;

	_buildindWord.append(&byte, 1);

	if (_buildindWord.size() == _wordSize)
	{
		_currentStage = CollectingParity;
		_parityValidator.clear();
	}
}