/*
 * SerialLink.h
 *
 *  Created on: 19.03.2019
 *      Author: Tim
 */

#ifndef COMLINK_SERIALLINK_H_
#define COMLINK_SERIALLINK_H_

#include <stdint.h>

#include "../../../../T3Framework/Components/driver/communication/CommunicationDriver.hpp"

/*
 * Name: 	SerialLink
 *
 * Purpose:	Implements the IComLink interface for communication over the serial line (UART).
 */
class SerialDriver: public CommunicationDriver
{
public:
	virtual ~SerialDriver();

	/*
	 * Name: 		initialize
	 *
	 * Purpose: 	Initializes the UART peripheral.
	 *
	 * Arguments: 	<none>
	 *
	 * Notes: This is called from the core app before any calls to read and write.
	 */
	virtual bool initialize();

	/*
	 * Name:		write
	 *
	 * Purpose: 	Sends an arbitrary amount of bytes over UART to the host
	 *
	 * Arguments: 	data - a pointer to the data buffer to be sent to the host
	 * 				count - the number of bytes to send from the data buffer
	 */
	virtual void write(const uint8_t* data, uint32_t count);

	/*
	 * Name:		read
	 *
	 * Purpose: 	Reads a byte from the UART peripheral for further processing
	 *
	 * Arguments: 	<none>
	 */
	virtual uint8_t read();
};

#endif /* COMLINK_SERIALLINK_H_ */
