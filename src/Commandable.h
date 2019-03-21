/*
 * Commandable.h
 *
 *  Created on: 21.03.2019
 *      Author: Tim
 */

#ifndef COMMANDABLE_H_
#define COMMANDABLE_H_

#include <stdint.h>
#include <buffer.h>

class ICommandable
{
public:
	virtual buffer_t<char>* getCommandBuffer() = 0;
	virtual void accept() = 0;
};

template<uint32_t N>
class Commandable: public ICommandable
{
protected:
	char internal_buffer[N];
	buffer_t<char> buffer;
public:
	Commandable()
	{
		buffer.assignBuffer(internal_buffer, N);
	}

	virtual ~Commandable()
	{

	}

	virtual buffer_t<char>* getCommandBuffer()
	{
		return &buffer;
	}
};

#endif /* COMMANDABLE_H_ */
