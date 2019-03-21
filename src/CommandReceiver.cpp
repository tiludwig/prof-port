/*
 * CommandReceiver.cpp
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#include <CommandReceiver.h>

CommandReceiver::CommandReceiver()
{
	cmdBuffer = nullptr;
	receivedId = 0;
	bytesToReceive = 0;
	runningSum = 0;

	invalidCommandsCounter = 0;

	state = WaitingForStart;
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

void CommandReceiver::process(char data)
{
	runningSum += data;
	switch (state)
	{
	case WaitingForStart:
		if (data == startMarker)
		{
			state = ReadingId;
			runningSum = 0;
		}
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
		}
		else
		{
			auto entry = getRoutingEntryForId(receivedId);
			auto target = entry->target;
			target->accept();
		}
		break;
	}
}
