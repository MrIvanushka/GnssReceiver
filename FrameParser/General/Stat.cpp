#include "Stat.h"

#include "Log.h"

Stat::Stat(const std::string& name, const std::unordered_map<StatKey, std::string>& definedNames) :
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