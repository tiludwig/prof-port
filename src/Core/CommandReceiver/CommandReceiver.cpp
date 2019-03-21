/*
 * CommandReceiver.cpp
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#include "CommandReceiver.h"

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
	for (uint8_t i = 0; i < 4; i++)
	{
		if (routingTable[i].id == id)
			return &routingTable[i];
	}

	return nullptr;
}

bool CommandReceiver::process(char data)
{
	// check if data is start symbol
	if (data == '#')
	{
		// change state from waiting to receiving
		state = ReceivingId;
		return false;
	}

	// check if byte needs to be destuffed
	if (data == '?')
	{
		needsDestuffing = true;
		return false;
	}

	if (needsDestuffing)
	{
		needsDestuffing = false;
		data = data ^ 0x20;
	}

	bool result = false;

	switch (state)
	{
	case WaitingForStart:
		break;
	case ReceivingId:
	{
		receivedId = data;
		auto routingEntry = getRoutingEntryForId(receivedId);
		if (routingEntry == nullptr)
		{
			state = WaitingForStart;
		}
		else
		{
			cmdBuffer = routingEntry->buffer;
			cmdBuffer->clear();
			state = ReceivingSizeMSB;
		}
		break;
	}
	case ReceivingSizeMSB:
		bytesToReceive = ((uint16_t) data) << 8;
		state = ReceivingSizeLSB;
		break;

	case ReceivingSizeLSB:
		bytesToReceive |= data;
		if (bytesToReceive == 0)
			state = ReceivingChecksum;
		else
			state = ReceivingPayload;
		break;
	case ReceivingPayload:
		cmdBuffer->push_back(data);
		bytesToReceive--;
		if (bytesToReceive == 0)
			state = ReceivingChecksum;
		break;
	case ReceivingChecksum:
		if ( (runningSum + (int8_t)data) != 0)
		{
			invalidCommandsCounter++;
			result = false;
		}
		else
		{
			auto entry = getRoutingEntryForId(receivedId);
			auto target = entry->target;
			target->accept();
			result = true;
		}
		state = WaitingForStart;
		break;
	}

	runningSum += data;
	return result;

	/*runningSum += data;

	 // check for start symbol
	 if (data == startMarker)
	 {
	 state = ReadingId;
	 runningSum = 0;
	 return false;
	 }

	 bool result = false;

	 switch (state)
	 {
	 case WaitingForStart:
	 break;
	 case ReadingId:
	 {
	 receivedId = data;
	 auto routingEntry = getRoutingEntryForId(receivedId);
	 if (routingEntry == nullptr)
	 {
	 state = WaitingForStart;
	 }
	 else
	 {
	 cmdBuffer = routingEntry->buffer;
	 cmdBuffer->clear();
	 state = ReadingSizeLSB;
	 }
	 break;
	 }
	 case ReadingSizeLSB:
	 bytesToReceive = ((uint16_t) data) << 8;
	 state = ReadingSizeMSB;
	 break;

	 case ReadingSizeMSB:
	 bytesToReceive |= data;
	 if(bytesToReceive == 0)
	 state = ReadingChecksum;
	 else
	 state = ReadingData;
	 break;

	 case ReadingData:
	 cmdBuffer->push_back(data);
	 bytesToReceive--;
	 if (bytesToReceive == 0)
	 state = ReadingChecksum;
	 break;

	 case ReadingChecksum:
	 if (runningSum != 0)
	 {
	 invalidCommandsCounter++;
	 result = false;
	 }
	 else
	 {
	 auto entry = getRoutingEntryForId(receivedId);
	 auto target = entry->target;
	 target->accept();
	 result = true;
	 }
	 state = WaitingForStart;

	 break;
	 }

	 return result;*/
}
