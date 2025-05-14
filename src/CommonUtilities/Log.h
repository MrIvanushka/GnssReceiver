#pragma once

#include <chrono>
#include <format>
#include <iostream>
#include <mutex>
#include <source_location>
#include <stack>
#include <syncstream>
#include <unordered_map>
#include <set>

namespace gnssRecv
{

enum class Level
{
	Debug,
	Info,
	Warn,
	Error
};

enum class PartsOfLog
{
	Level,
	Date,
	Timestamp,
	Data
};

class ILoggerListener
{
public:
	virtual ~ILoggerListener() = default;

	virtual void handleLog(Level, std::string text, std::string timestamp) = 0;
};

class Logger
{
public:
	Logger(const Logger& logger) = delete;
	Logger& operator=(const Logger&) = delete;

	static Logger& instance()
	{
		static Logger logger;
		return logger;
	}

	void addListener(ILoggerListener* listener)
	{
		_listeners.insert(listener);
	}

	void removeListener(ILoggerListener* listener)
	{
		_listeners.erase(listener);
	}

	template<typename... Args>
	void log(const Level& level, Args&&... args)
	{
		std::unordered_map<PartsOfLog, std::string> partsOfLog = formateLog(level, args...);
		if (partsOfLog.empty())
			return;

		for (auto listener : _listeners)
		{
			listener->handleLog(level, partsOfLog[PartsOfLog::Data], partsOfLog[PartsOfLog::Date]);
		}

		std::osyncstream syncStream(*_out);
		syncStream
			<< "[   " << partsOfLog[PartsOfLog::Level] << "  ]"
			<< "[" << partsOfLog[PartsOfLog::Date] << "] "
			<< partsOfLog[PartsOfLog::Data]
			<< std::endl;
	}
protected:
	explicit Logger(std::ostream& out = std::cout) :
		_out(&out),
		_levelColors(colorLevels()),
		_turnedOnLevels(turnOnAllLevels())
	{}

	~Logger() = default;

private:
	static std::unordered_map<Level, std::string> colorLevels()
	{
		return
		{
			{ Level::Debug,	"\x1b[1;35mDEBUG\x1b[0m" },
			{ Level::Error,	"\x1b[31mERROR\x1b[0m" },
			{ Level::Info,	"\x1b[36mINFO\x1b[0m" },
			{ Level::Warn,	"\x1b[33mWARN\x1b[0m" }
		};
	}

	static std::unordered_map<Level, std::string> uncolorLevels()
	{
		return
		{
			{ Level::Debug,	"DEBUG" },
			{ Level::Error,	"ERROR" },
			{ Level::Info,	"INFO" },
			{ Level::Warn,	"WARN" }
		};
	}

	static std::unordered_map<Level, bool> turnOnAllLevels()
	{
		return
		{
			{ Level::Debug,	true },
			{ Level::Error,	true },
			{ Level::Info,	true },
			{ Level::Warn,	true }
		};
	}

	template<typename... Args>
	std::unordered_map<PartsOfLog, std::string> formateLog(const Level& level, Args&&... args)
	{
		if (!_turnedOnLevels.contains(level) ||
			!_turnedOnLevels.at(level) ||
			!_levelColors.contains(level))
			return {};

		std::ostringstream messageStream;
		(messageStream << ... << std::forward<Args>(args)); // Выражения свёртки

		const auto now = std::chrono::system_clock::now();
		const std::string date = std::format("{:%F %T %Z}", std::chrono::zoned_time{ std::chrono::current_zone(), now });
		const std::string timestamp = std::to_string(now.time_since_epoch().count());

		return std::unordered_map<PartsOfLog, std::string>({
				{ PartsOfLog::Level, _levelColors.at(level) },
				{ PartsOfLog::Date, date },
				{ PartsOfLog::Timestamp, timestamp},
				{ PartsOfLog::Data, messageStream.str() }
			});

	}

	std::ostream* _out;

	bool _printFullFunctionName;
	std::unordered_map<Level, std::string> _levelColors;
	std::unordered_map<Level, bool> _turnedOnLevels;

	std::set<ILoggerListener*> _listeners;
};

} //namespace gnssRecv

#define LOG_INFO(...) gnssRecv::Logger::instance().log(gnssRecv::Level::Info, __VA_ARGS__)
#define LOG_WARN(...) gnssRecv::Logger::instance().log(gnssRecv::Level::Warn, __VA_ARGS__)
#define LOG_ERROR(...) gnssRecv::Logger::instance().log(gnssRecv::Level::Error, __VA_ARGS__)
