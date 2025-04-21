#include "ByteData.h"

using namespace gnssRecv::frameParser;

ByteData::ByteData() : _offset(0), _data({})
{}

ByteData::ByteData(uint8_t value, size_t size) :
	_offset(0),
	_data(size, value)
{}

ByteData::ByteData(uint8_t* data, size_t size) :
	_offset(0),
	_data(size)
{
	memcpy(_data.data(), data, size);
}

void ByteData::append(uint8_t* data, size_t size)
{
	auto oldSize = _data.size();
	_data.resize(oldSize + size);
	memcpy(_data.data() + oldSize, data, size);
}

void ByteData::append(const ByteData& otherData)
{
	auto oldSize = _data.size();
	_data.resize(oldSize + otherData.size());
	memcpy(_data.data() + oldSize, otherData.cdata(), otherData.size());
}

bool ByteData::removeLeft(size_t cutSize)
{
	if (size() < cutSize)
		return false;

	_offset += cutSize;
	return true;
}

void ByteData::invert()
{
	for (auto i = _offset; i < _data.size(); ++i)
		_data[i] = ~_data[i];
}

void ByteData::clear()
{
	_offset = 0;
	_data.clear();
}

size_t ByteData::size() const
{
	return _data.size() - _offset;
}

const uint8_t* ByteData::cdata() const
{
	return _data.data() + _offset;
}