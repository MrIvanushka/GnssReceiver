#pragma once

#include "ByteCollector.h"
#include "ByteData.h"

namespace gnssRecv
{
namespace frameParser
{

class WordCollector
{
public:
	enum CollectResult
	{
		Ok,
		StillCollecting,
		ParityError
	};
private:
	class ParityValidator
	{
	public:
		CollectResult validate(uint8_t bit, ByteData& word);

		void clear();
	private:
		bool checkParity(ByteData& word);
	private:
		uint8_t _buildingParity = 0;
		uint8_t _filledBitsCount = 0;

		//last bits of previous word
		uint8_t _D29 = 0;
		uint8_t _D30 = 0;
	};

	enum Stage
	{
		CollectingPayload,
		CollectingParity
	};
public:
	CollectResult collectBit(uint8_t bit, ByteData* ret);

	void mentionBytes(const ByteData&);

	void clear();
private:
	void buildPayload(uint8_t bit);
private:
	const uint8_t _wordSize = 3;

	Stage _currentStage = CollectingPayload;

	ByteData _buildindWord;

	ByteCollector _byteCollector;
	ParityValidator _parityValidator;
};

} //namespace frameParser

} //namespace gnssRecv