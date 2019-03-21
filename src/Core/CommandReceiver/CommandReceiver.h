/*
 * CommandReceiver.h
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#ifndef COMMANDRECEIVER_H_
#define COMMANDRECEIVER_H_

#include <Components/ComLink/IComLink.hpp>
#include <Core/Buffer/basic_buffer.h>
#include <Core/Buffer/switchable_buffer.h>
#include "Commandable.h"



struct command_t
{
	uint8_t id;
	uint16_t size;
	char* payload;
};

enum ReceiverState
{
	WaitingForStart,
	ReceivingId,
	ReceivingSizeMSB,
	ReceivingSizeLSB,
	ReceivingPayload,
	ReceivingChecksum,
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
	static constexpr char startMarker = '#';

	buffer_t<char>* cmdBuffer;

	basic_buffer<struct routing_entry_t, 4> routingTable;

	uint8_t receivedId;
	uint16_t bytesToReceive;

	int8_t runningSum;

	ReceiverState state;
	bool needsDestuffing;
public:
	uint32_t invalidCommandsCounter;

public:
	CommandReceiver();

	void registerComponent(uint8_t id, ICommandable* target);

	routing_entry_t* getRoutingEntryForId(uint8_t id);

	bool process(char data);
};

#endif /* COMMANDRECEIVER_H_ */
