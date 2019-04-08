/*
 * bufferedstream.h
 *
 *  Created on: 21.03.2019
 *      Author: Tim
 */

#ifndef CORE_READER_PAYLOADREADER_H_
#define CORE_READER_PAYLOADREADER_H_

#include <stdint.h>

class PayloadReader
{
private:
	char* data;
	uint32_t index;
public:
	PayloadReader(char* data);

	PayloadReader(char* data, uint32_t offset);

	template<class T>
	T read();

	void readString(char* buffer);
};

template<class T>
T PayloadReader::read()
{
	T value = 0;
	for (unsigned int i = 0; i < sizeof(value); i++)
	{
		unsigned char temp = static_cast<unsigned char>(data[index++]);
		value = value | (static_cast<T>(temp) << 8 * i);
	}

	index += sizeof(value);
	return value;
}

#endif /* CORE_READER_PAYLOADREADER_H_ */
