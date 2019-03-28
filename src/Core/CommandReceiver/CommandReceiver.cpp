/*
 * CommandReceiver.cpp
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#include "CommandReceiver.h"

void CommandReceiver::genStartSymbol()
{
	uint8_t startSymbol = '#';
	link->write(&startSymbol, 1);
}
void CommandReceiver::writeAndStuff(char value)
{
	if (value == '?' || value == '#')
	{
		uint8_t stuff = '?';
		link->write(&stuff, 1);
		value = value ^ 0x20;
	}

	link->write(reinterpret_cast<uint8_t*>(&value), 1);
}

CommandReceiver::CommandReceiver()
{
	cmdBuffer = nullptr;
	receivedId = 0;
	bytesToReceive = 0;
	runningSum = 0;

	invalidCommandsCounter = 0;

	state = WaitingForStart;
	needsDestuffing = false;
}

void CommandReceiver::registerComponent(uint8_t id, ICommandable* target)
{
	routing_entry_t entry;
	entry.id = id;
	entry.buffer = target->getCommandBuffer();
	entry.target = target;
	routingTable.push_back(entry);
}

struct routing_entry_t* CommandReceiver::getRoutingEntryForId(uint8_t id)
{
	for (uint8_t i = 0; i < MAX_ROUTING_ENTRIES; i++)
	{
		if (routingTable[i].id == id)
			return &routingTable[i];
	}

	return nullptr;
}

void CommandReceiver::resetReceiver()
{
	state = ReceivingId;
	runningSum = 0;
}

bool CommandReceiver::setReceiveBufferToTargetBuffer()
{
	// get routing entry
	auto routingEntry = getRoutingEntryForId(receivedId);
	if (routingEntry == nullptr)
	{
		return false;
	}

	auto target = routingEntry->target;
	cmdBuffer = target->getCommandBuffer();
	cmdBuffer->clear();
	return true;
}

bool CommandReceiver::process(uint8_t value)
{
	runningSum += (int8_t) value;
	bool commandReceived = false;

	switch (state)
	{
	case WaitingForStart:
		break;
	case ReceivingId:
		receivedId = value;
		if (setReceiveBufferToTargetBuffer() == false)
		{
			state = WaitingForStart;
		}
		else
		{
			state = ReceivingSizeMSB;
		}
		break;

	case ReceivingSizeMSB:
		bytesToReceive = ((uint16_t) value << 8);
		state = ReceivingSizeLSB;
		break;

	case ReceivingSizeLSB:
		bytesToReceive |= value;
		state = ReceivingPayload;
		break;

	case ReceivingPayload:
		cmdBuffer->push_back(value);
		if (--bytesToReceive == 0)
		{
			state = ReceivingChecksum;
		}
		break;

	case ReceivingChecksum:
		if (runningSum == 0)
		{
			commandReceived = true;
		}
		state = WaitingForStart;
		break;
	}

	return commandReceived;
}

bool CommandReceiver::isStartSymbol(uint8_t value)
{
	return (value == '#');
}

bool CommandReceiver::isByteStuffed(uint8_t value)
{
	return (value == '?');
}

void CommandReceiver::signalCommandReceived()
{
	// get routing entry
	auto routingEntry = getRoutingEntryForId(receivedId);
	if (routingEntry == nullptr)
		return;

	auto target = routingEntry->target;
	if (target == nullptr)
		return;

	// signal command received
	target->accept(link, receivedId);
}

void CommandReceiver::sendOk(uint8_t id)
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

void CommandReceiver::waitForCommand()
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

		if (commandReceived == true)
		{
			signalCommandReceived();
		}

	}
}
