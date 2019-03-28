/*
 * CommandReceiver.h
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#ifndef PACKETRECEIVER_H_
#define PACKETRECEIVER_H_

#ifndef MAX_ROUTING_ENTRIES
#define MAX_ROUTING_ENTRIES	8
#endif

#include <Components/ComLink/IComLink.hpp>
#include <Core/Buffer/RingBuffer.h>
#include <Core/DataLink/Packet.h>

#include <TTTProfConfig.h>

namespace States
{
enum ReceiverState
{
	WaitingForStart,
	ReceivingId,
	ReceivingSizeMSB,
	ReceivingSizeLSB,
	ReceivingPayload,
	ReceivingChecksum,
};
}
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
class PacketReceiver
{
private:
	RingBuffer<char, tttConfig_MAX_RECV_PACKET_SIZE> receiveBuffer;

private:
	uint8_t receivedId;
	uint16_t bytesToReceive;
	uint16_t packetSize;

	int8_t runningSum;

	States::ReceiverState state;
	bool needsDestuffing;
	IComLink* link;
public:
	uint32_t invalidCommandsCounter;

private:
	bool isStartSymbol(uint8_t value);
	bool isByteStuffed(uint8_t value);
	bool process(uint8_t value);
	void resetReceiver();

	void genStartSymbol();
	void writeAndStuff(char value);
public:
	PacketReceiver();

	void setLink(IComLink* comlink)
	{
		link = comlink;
	}

	void sendOk(uint8_t id);

	packet_t getPacket();
	void waitForCommand();
};

#endif /* PACKETRECEIVER_H_ */
