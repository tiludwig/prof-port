/*
 * CommandReceiver.h
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#ifndef COMMANDRECEIVER_H_
#define COMMANDRECEIVER_H_

#ifndef MAX_ROUTING_ENTRIES
#define MAX_ROUTING_ENTRIES	8
#endif

#include <Components/ComLink/IComLink.hpp>
#include <Core/Buffer/basic_buffer.h>
#include <Core/Buffer/buffer.h>
#include "ICommandable.h"

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

/*
 * Name:		CommandReceiver
 *
 * Purpose:		Receives and decodes commands from the communication
 * 				interface. After decoding, the CommandReceiver will
 * 				notify any associated modules, that implement the
 * 				ICommandable interface, a new command has been recei-
 * 				ved.
 *
 * Note:		The maximum number of associated modules is defined
 * 				by the MAX_ROUTING_ENTRIES symbol and defaults to 8.
 *
 * Todo: 		Separate the protocol implementation from the decoding
 * 				and forwarding.
 */
class CommandReceiver
{
private:
	static constexpr char startMarker = '#';

	buffer_t<char>* cmdBuffer;

	basic_buffer<struct routing_entry_t, MAX_ROUTING_ENTRIES> routingTable;

	uint8_t receivedId;
	uint16_t bytesToReceive;

	int8_t runningSum;

	ReceiverState state;
	bool needsDestuffing;
	IComLink* link;
public:
	uint32_t invalidCommandsCounter;

private:
	bool isStartSymbol(uint8_t value);
	bool isByteStuffed(uint8_t value);
	bool process(uint8_t value);
	void resetReceiver();
	void signalCommandReceived();
	bool setReceiveBufferToTargetBuffer();

	void genStartSymbol();
	void writeAndStuff(char value);
public:
	CommandReceiver();

	void setLink(IComLink* comlink)
	{
		link = comlink;
	}

	void sendOk(uint8_t id);

	void registerComponent(uint8_t id, ICommandable* target);

	routing_entry_t* getRoutingEntryForId(uint8_t id);

	void waitForCommand();
};

#endif /* COMMANDRECEIVER_H_ */
