#pragma once

#include <unordered_map>
#include <memory>
#include <cstdint>
#include <string>

typedef uint32_t StatKey;
typedef uint64_t StatValue;

namespace gnssRecv
{

class Stat
{
public:
	Stat(const std::string& name, const std::unordered_map<StatKey, std::string>& definedNames);

	Stat() = default;
	Stat(const Stat&) = default;

	Stat& operator=(const Stat&) = default;

	void clear();

	void increment(StatKey);

	const std::string& name() const { return _name; }

	const std::string& paramName(StatKey key) const;

	const std::unordered_map<StatKey, StatValue>& values() const { return _values; }
private:
	std::string _name;
	std::unordered_map<StatKey, std::string> _names;
	std::unordered_map<StatKey, StatValue> _values;
};

} //namespace gnssRecv