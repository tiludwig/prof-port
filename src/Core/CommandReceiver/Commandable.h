/*
 * Commandable.h
 *
 *  Created on: 21.03.2019
 *      Author: Tim
 */

#ifndef COMMANDABLE_H_
#define COMMANDABLE_H_

#include <stdint.h>
#include <Core/Buffer/buffer.h>
#include "ICommandable.h"

/*
 * Name:	Commandable
 *
 * Purpose:	Provides a standard implementation to be used by
 * 			commandable modules. It uses a internal statically
 * 			allocated memory buffer for the command buffer.
 * 			The size of the buffer is configurable by the
 * 			implementor.
 *
 * Implements: Partially implements the ICommandable interface
 */
template<uint32_t N>
class Commandable: public ICommandable
{
protected:
	char internal_buffer[N];
	buffer_t<char> buffer;
public:
	/*
	 * Name:	Commandable
	 *
	 * Purpose:	Creates a new object and initializes the buffer
	 * 			to use the internal static memory array.
	 */
	Commandable()
	{
		buffer.assignBuffer(internal_buffer, N);
	}

	virtual ~Commandable()
	{

	}

	/*
	 * Name:	getCommandBuffer
	 *
	 * Purpose:	Used by the command receiver to acquire the buffer to
	 * 			store command data into. The pointer to the buffer must
	 * 			point to a valid memory location.
	 */
	virtual buffer_t<char>* getCommandBuffer()
	{
		return &buffer;
	}
};

#endif /* COMMANDABLE_H_ */
