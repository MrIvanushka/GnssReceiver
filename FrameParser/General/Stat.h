#pragma once

#include "Utility.h"
#include <unordered_map>
#include <memory>

typedef uint32_t StatKey;
typedef uint64_t StatValue;

class Stat
{
public:
	Stat(const std::string& name, const std::unordered_map<StatKey, std::string>& definedNames);

	void clear();

	void increment(StatKey);

	const std::string& name() const { return _name; }

	const std::unordered_map<StatKey, std::string>& definedNames() const { return _names; }

	const std::unordered_map<StatKey, StatValue>& values() const { return _values; }
private:
	std::string _name;
	std::unordered_map<StatKey, std::string> _names;
	std::unordered_map<StatKey, StatValue> _values;
};