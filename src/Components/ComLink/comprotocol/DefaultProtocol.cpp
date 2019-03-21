/*
 * DefaultProtocol.cpp
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#include <Components/ComLink/comprotocol/DefaultProtocol.h>

DefaultProtocol::~DefaultProtocol()
{
	// TODO Auto-generated destructor stub
}

bool DefaultProtocol::isPacketComplete()
{
	return false;
}

void DefaultProtocol::processByte(char data)
{
	switch (state)
	{
	case Waiting:
		tempCommand.id = data;
		state = ReadSizeLSB;
		break;
	case ReadSizeLSB:
		tempCommand.size = data;
		state = ReadSizeMSB;
		break;
	case ReadSizeMSB:
		tempCommand.size = (tempCommand.size << 8) | data;
		tempCommand.buffer = new char[tempCommand.size];
		if(tempCommand.buffer == nullptr)
			state = Waiting;

		state = ReadData;
	case ReadData:

		break;
	}
}

void DefaultProtocol::resetReceiver()
{

}
