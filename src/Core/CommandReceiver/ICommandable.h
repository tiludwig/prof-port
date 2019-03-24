/*
 * ICommandable.h
 *
 *  Created on: 24.03.2019
 *      Author: Tim
 */

#ifndef CORE_COMMANDRECEIVER_ICOMMANDABLE_H_
#define CORE_COMMANDRECEIVER_ICOMMANDABLE_H_

#include <stdint.h>
#include <Components/ComLink/IComLink.hpp>

/*
 * Name:	ICommandable
 *
 * Purpose:	Provides an interface for the command receiver to
 * 			acquire a buffer to store the command data into
 * 			without using dynamic memory allocation. The implementor
 * 			needs to provide sufficient space to store the data
 * 			into.
 *			Also allows the command receiver to signal the
 *			commandable module that new data is available for processing
 */
class ICommandable
{
public:
	/*
	 * Name:	getCommandBuffer
	 *
	 * Purpose:	Used by the command receiver to acquire the buffer to
	 * 			store command data into. The pointer to the buffer must
	 * 			point to a valid memory location.
	 */
	virtual buffer_t<char>* getCommandBuffer() = 0;

	/*
	 * Name:	accept
	 *
	 * Purpose:	Called by the command receiver when a command is received
	 * 			which is targeted for this commandable.
	 */
	virtual void accept(IComLink* sender, uint8_t id) = 0;
};

#endif /* CORE_COMMANDRECEIVER_ICOMMANDABLE_H_ */
