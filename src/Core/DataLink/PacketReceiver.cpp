/*
 * PacketReceiver.cpp
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#include "PacketReceiver.h"

void PacketReceiver::genStartSymbol()
{
	uint8_t startSymbol = '#';
	link->write(&startSymbol, 1);
}
void PacketReceiver::writeAndStuff(char value)
{
	if (value == '?' || value == '#')
	{
		uint8_t stuff = '?';
		link->write(&stuff, 1);
		value = value ^ 0x20;
	}

	link->write(reinterpret_cast<uint8_t*>(&value), 1);
}

PacketReceiver::PacketReceiver()
{
	receivedId = 0;
	bytesToReceive = 0;
	runningSum = 0;

	invalidCommandsCounter = 0;

	state = States::WaitingForStart;
	needsDestuffing = false;
}

void PacketReceiver::resetReceiver()
{
	state = States::ReceivingId;
	runningSum = 0;
}



bool PacketReceiver::process(uint8_t value)
{
	runningSum += (int8_t) value;
	bool commandReceived = false;

	switch (state)
	{
	case States::WaitingForStart:
		break;
	case States::ReceivingId:
		receivedId = value;

			state = States::ReceivingSizeLSB;

		break;

	case States::ReceivingSizeLSB:
			bytesToReceive = value;
			state = States::ReceivingSizeMSB;
			break;


	case States::ReceivingSizeMSB:
		bytesToReceive |= ((uint16_t) value << 8);
		packetSize = bytesToReceive;
		state = States::ReceivingPayload;
		break;


	case States::ReceivingPayload:
		receiveBuffer.append(value);
		if (--bytesToReceive == 0)
		{
			state = States::ReceivingChecksum;
		}
		break;

	case States::ReceivingChecksum:
		if (runningSum == 0)
		{
			commandReceived = true;
		}
		state = States::WaitingForStart;
		break;
	}

	return commandReceived;
}

bool PacketReceiver::isStartSymbol(uint8_t value)
{
	return (value == '#');
}

bool PacketReceiver::isByteStuffed(uint8_t value)
{
	return (value == '?');
}

void PacketReceiver::sendOk(uint8_t id)
{
	uint8_t lenLSB = 2;
	uint8_t lenMSB = 0;

	int8_t checksum = id;
	checksum += lenLSB;
	checksum += lenMSB;
	checksum += 'O';
	checksum += 'k';

	genStartSymbol();
	writeAndStuff(id);
	writeAndStuff(lenLSB);
	writeAndStuff(lenMSB);
	writeAndStuff('O');
	writeAndStuff('k');

	checksum = -checksum;
	writeAndStuff(checksum);
}

void PacketReceiver::waitForCommand()
{
	bool commandReceived = false;
	while (!commandReceived)
	{
		auto receivedByte = link->read();

		// check if start symbol is found in the stream
		if (isStartSymbol(receivedByte) == true)
		{
			resetReceiver();
			continue;
		}

		// check if the byte was stuffed
		// if so, destuff it
		if (isByteStuffed(receivedByte) == true)
		{
			receivedByte = link->read();
			receivedByte = receivedByte ^ 0x20;
		}

		// process the received byte
		commandReceived = process(receivedByte);
	}
}

packet_t PacketReceiver::getPacket()
{
	packet_t packet;
	packet.id = receivedId;
	packet.size = packetSize;
	packet.payload = receiveBuffer.getCurrentItemAddress();
	receiveBuffer.skip(packet.size);
	packet.checksum = 0;

	return packet;
}
