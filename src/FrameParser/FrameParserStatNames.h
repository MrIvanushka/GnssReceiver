#pragma once

#include <unordered_map>
#include <string>
#include "Stat.h"

namespace gnssRecv
{
namespace frameParser
{

class FrameParserStatNames
{
public:
	enum FrameParserStatKey
	{
		BitCollectorStat,
		SubframeCollectorStat,
		SubframeParserStat,

		ReceivedSignals,
		CollectedBits,
		BitErrors,
		ReceivedBits,
		ProducedWords,
		ProducedSubframes,
		TlmSyncronizationErrors,
		ParityErrors,
		ReceivedSubframes,
		ProducedSatClock,
		ProducedEphemeris1,
		ProducedEphemeris2,
		ProducedAlmanac1,
		ProducedAlmanac2,
	};

	static inline std::unordered_map<StatKey, std::string> names =
	{
		{ BitCollectorStat, "���������� �������������� ���" },
		{ SubframeCollectorStat, "���������� �������������� ���������" },
		{ SubframeParserStat, "���������� ����������� ���������" },

		{ ReceivedSignals, "������� ������� �������" },
		{ CollectedBits, "������ ���" },
		{ BitErrors, "����� ������������� ���" },
		{ ReceivedBits, "������� ���" },
		{ ProducedWords, "�������� ����" },
		{ ProducedSubframes, "������ ���������" },
		{ TlmSyncronizationErrors, "������ ������������� ���������" },
		{ ParityErrors, "������ �������� ��������" },
		{ ReceivedSubframes, "������� ���������" },
		{ ProducedSatClock, "������� ���������� � ������� (ID=1)" },
		{ ProducedEphemeris1, "������� ����������� ������ (ID=2)" },
		{ ProducedEphemeris2, "������� ����������� ������ (ID=3)" },
		{ ProducedAlmanac1, "������� ������ ��������� (ID=4)" },
		{ ProducedAlmanac2, "������� ������ ��������� (ID=5)" },
	};
};

} //namespace frameParser

} //namespace gnssRecv