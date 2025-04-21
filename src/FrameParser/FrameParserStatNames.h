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
		{ BitCollectorStat, "Статистика синхронизатора бит" },
		{ SubframeCollectorStat, "Статистика синхронизатора подкадров" },
		{ SubframeParserStat, "Статистика обработчика подкадров" },

		{ ReceivedSignals, "Принято отчётов сигнала" },
		{ CollectedBits, "Отдано бит" },
		{ BitErrors, "Сбоев синхронизации бит" },
		{ ReceivedBits, "Принято бит" },
		{ ProducedWords, "Получено слов" },
		{ ProducedSubframes, "Отдано подкадров" },
		{ TlmSyncronizationErrors, "Ошибок синхронизации преамбулы" },
		{ ParityErrors, "Ошибок проверки чётности" },
		{ ReceivedSubframes, "Принято подкадров" },
		{ ProducedSatClock, "Принято информации о времени (ID=1)" },
		{ ProducedEphemeris1, "Принято эфемеридных данных (ID=2)" },
		{ ProducedEphemeris2, "Принято эфемеридных данных (ID=3)" },
		{ ProducedAlmanac1, "Принято частей альманаха (ID=4)" },
		{ ProducedAlmanac2, "Принято частей альманаха (ID=5)" },
	};
};

} //namespace frameParser

} //namespace gnssRecv