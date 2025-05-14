#include "Stat.h"

#include "Log.h"

using namespace gnssRecv;

Stat::Stat(const std::string& name, const std::unordered_map<StatKey, std::string>& definedNames) :
	_name(name),
	_names(definedNames)
{
	for (const auto& pair : definedNames)
		_values[pair.first] = 0;
}

void Stat::clear()
{
	for (const auto& pair : _values)
		_values[pair.first] = 0;
}

void Stat::increment(StatKey key)
{
	auto valueIt = _values.find(key);

	if (valueIt == _values.end())
	{
		LOG_ERROR("Trying to increment unknown stat key!");
		return;
	}
	valueIt->second += 1;
}

const std::string& Stat::paramName(StatKey key) const
{
	auto nameIt = _names.find(key);

	if (nameIt == _names.end())
	{
		LOG_ERROR("Trying to get unknown name!");
		return "";
	}
	return nameIt->second;
}

StatValue Stat::value(StatKey key) const
{
	auto valueIt = _values.find(key);

	if (valueIt == _values.end())
	{
		return 0;
	}
	return valueIt->second;
}