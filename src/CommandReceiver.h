/*
 * CommandReceiver.h
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#ifndef COMMANDRECEIVER_H_
#define COMMANDRECEIVER_H_

#include "Target.h"
#include <comlink/IComLink.hpp>
#include <switchable_buffer.h>
#include <basic_buffer.h>
#include <Commandable.h>

struct command_t
{
	uint8_t id;
	uint16_t size;
	char* payload;
};

enum ReceiverState
{
	WaitingForStart,
	ReadingId,
	ReadingSizeMSB,
	ReadingSizeLSB,
	ReadingData,
	ReadingChecksum
};

struct routing_entry_t
{
	uint8_t id;
	buffer_t<char>* buffer;
	ICommandable* target;
};

class CommandReceiver
{
private:
	const char startMarker = '#';

	buffer_t<char>* cmdBuffer;

	basic_buffer<struct routing_entry_t, 4> routingTable;

	uint8_t receivedId;
	uint16_t bytesToReceive;

	int8_t runningSum;

	ReceiverState state;
	uint32_t invalidCommandsCounter;
public:
	CommandReceiver();

	void registerComponent(uint8_t id, ICommandable* target);

	routing_entry_t* getRoutingEntryForId(uint8_t id);

	void process(char data);
};

#endif /* COMMANDRECEIVER_H_ */
