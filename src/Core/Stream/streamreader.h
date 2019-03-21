/*
 * bufferedstream.h
 *
 *  Created on: 21.03.2019
 *      Author: Tim
 */

#ifndef CORE_STREAM_STREAMREADER_H_
#define CORE_STREAM_STREAMREADER_H_

#include <core/Buffer/buffer.h>

class streamreader
{
private:
	buffer_t<char> internal_buffer;
	uint32_t read_position;
private:
	virtual void append(char value);
public:
	streamreader(buffer_t<char>& buffer);
	streamreader(char* buffer, uint32_t size);
	streamreader(buffer_t<char> && buffer);

	virtual ~streamreader();

	uint32_t bytesAvailable();

	template<class T>
	T read();
};

template<class T>
T streamreader::read()
{
	if (bytesAvailable() < sizeof(T))
		return 0;

	T value = 0;
	for (unsigned int i = 0; i < sizeof(value); i++)
	{
		unsigned char temp = static_cast<unsigned char>(internal_buffer[read_position++]);
		value = value | (static_cast<T>(temp) << 8 * i);
	}
	return value;
}

#endif /* CORE_STREAM_STREAMREADER_H_ */
