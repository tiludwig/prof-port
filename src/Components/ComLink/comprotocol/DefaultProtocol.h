/*
 * DefaultProtocol.h
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#ifndef COMLINK_COMPROTOCOL_DEFAULTPROTOCOL_H_
#define COMLINK_COMPROTOCOL_DEFAULTPROTOCOL_H_

#include <Components/ComLink/comprotocol/IComProtocol.hpp>
#include <stdint.h>

struct command_t
{
	char id;
	uint16_t size;
	char* buffer;
};

class DefaultProtocol: public IComProtocol
{
private:
	command_t tempCommand;

	enum ReceiverState
	{
		Waiting,
		ReadSizeLSB,
		ReadSizeMSB,
		ReadData,
	} state;
public:
	virtual ~DefaultProtocol();

	virtual bool isPacketComplete();
	virtual void processByte(char data);
	virtual void resetReceiver();
};

#endif /* COMLINK_COMPROTOCOL_DEFAULTPROTOCOL_H_ */
