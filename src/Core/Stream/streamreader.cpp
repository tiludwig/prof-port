/*
 * bufferedstream.cpp
 *
 *  Created on: 21.03.2019
 *      Author: Tim
 */

#include <Core/Stream/streamreader.h>

streamreader::~streamreader()
{
	// TODO Auto-generated destructor stub
}

streamreader::streamreader(buffer_t<char>& buffer)
{
	read_position = 0;
	internal_buffer = buffer;
}

streamreader::streamreader(char* buffer, uint32_t size)
{
	read_position = 0;
	internal_buffer.assignBuffer(buffer, size);
}

streamreader::streamreader(buffer_t<char> && buffer)
{
	read_position = 0;
	internal_buffer = buffer;
	buffer.assignBuffer(nullptr, 0);
}

void streamreader::append(char value)
{
	internal_buffer.push_back(value);
}

uint32_t streamreader::bytesAvailable()
{
	int32_t result = (internal_buffer.getCount() - read_position);
	if (result < 0)
		result = 0;

	return result;
}

template <>
char streamreader::read()
{
	return internal_buffer[read_position++];
}

template <>
bool streamreader::read()
{
	auto value = internal_buffer[read_position++];
	return (value == 0) ? false : true;
}
