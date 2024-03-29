/*
 * IComLink.hpp
 *
 *  Created on: 19.03.2019
 *      Author: Tim
 */

#ifndef COMLINK_ICOMLINK_HPP_
#define COMLINK_ICOMLINK_HPP_

#include <stdint.h>

/*
 * Name: 	IComLink
 *
 * Purpose:	Provides a well-defined interface for the host communication module.
 *
 * 			The 'initialize' method should be used to initialize the comm driver
 * 			being used (or the comm peripheral in bare-metal applications).
 *
 * 			The two methods 'write' and 'read' should provide a mean for sending
 * 			an arbitrary amount of bytes and receiving a single byte from the
 * 			communication interface for further processing.
 */
class CommunicationDriver
{
public:
	/*
	 * Name: 		initialize
	 *
	 * Purpose: 	Initializes the comm driver (or the comm peripheral).
	 *
	 * Arguments: 	<none>
	 *
	 * Notes: This is called from the core app before any calls to read and write.
	 */
	virtual bool initialize() = 0;

	/*
	 * Name:		write
	 *
	 * Purpose: 	Sends an arbitrary amount of bytes over the communication channel
	 * 				to the host.
	 *
	 * Arguments: 	data - a pointer to the data buffer to be sent to the host
	 * 				count - the number of bytes to send from the data buffer
	 */
	virtual void write(const uint8_t* data, uint32_t count) = 0;

	/*
	 * Name:		read
	 *
	 * Purpose: 	Reads a byte from the communication interface for further processing
	 *
	 * Arguments: 	<none>
	 */
	virtual uint8_t read() = 0;
};
#endif /* COMLINK_ICOMLINK_HPP_ */
