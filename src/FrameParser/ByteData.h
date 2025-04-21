#pragma once

#include <cstdint>
#include <vector>

namespace gnssRecv
{
namespace frameParser
{

class ByteData
{
public:
	ByteData();

	ByteData(uint8_t value, size_t size);

	ByteData(uint8_t* data, size_t size);

	ByteData(const ByteData&) = default;

	void append(uint8_t* data, size_t size);

	void append(const ByteData&);

	bool removeLeft(size_t size);

	void invert();

	void clear();

	size_t size() const;

	const uint8_t* cdata() const;

	template<typename Descr>
	bool castTo(Descr* descr)
	{
		auto descrSize = sizeof(Descr);
		if (size() < descrSize)
			return false;

		const auto src = &(_data[_offset]);
		memcpy(descr, src, descrSize);
		return true;
	}

	template<typename Descr>
	bool castToAndRemoveLeft(Descr* descr)
	{
		if (!castTo(descr))
			return false;
		return removeLeft(sizeof(Descr));
	}
private:
	size_t _offset = 0;
	std::vector<uint8_t> _data;
};

} //namespace frameParser

} //namespace gnssRecv