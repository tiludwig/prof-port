/*
 * bufferedstream.cpp
 *
 *  Created on: 21.03.2019
 *      Author: Tim
 */

#include <Core/Reader/PayloadReader.h>

PayloadReader::PayloadReader(char* data)
{
	this->data = data;
	index = 0;
}

PayloadReader::PayloadReader(char* data, uint32_t offset)
{
	this->data = data;
	index = offset;
}
