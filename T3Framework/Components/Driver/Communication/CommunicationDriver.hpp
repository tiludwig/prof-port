/*
 * CommunicationDriver.hpp
 *
 *  Created on: 19.03.2019
 *      Author: Tim
 */

#ifndef COMPONENTS_COMMUNICATIONDRIVER_HPP_
#define COMPONENTS_COMMUNICATIONDRIVER_HPP_

#include <stdint.h>

/*
 * Name: 	Communication driver
 *
 * Purpose:	Provides an interface for the host communication module.
 */
class CommunicationDriver
{
public:
	virtual ~CommunicationDriver()
	{
	}

	/*
	 * Name: 		initialize
	 *
	 * Purpose: 	Initializes the driver.
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
	 * 				This method should be implemented so that the process that runs the
	 * 				framework is suspended, so that other task can run.
	 *
	 * Arguments: 	<none>
	 */
	virtual uint8_t read() = 0;
};
#endif /* COMLINK_ICOMLINK_HPP_ */
