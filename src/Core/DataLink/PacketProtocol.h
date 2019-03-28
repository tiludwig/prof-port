/*
 * PacketProtocol.h
 *
 *  Created on: 28.03.2019
 *      Author: Tim
 */

#ifndef CORE_DATALINK_PACKETPROTOCOL_H_
#define CORE_DATALINK_PACKETPROTOCOL_H_

#include <TTTProfConfig.h>
#include <Core/Buffer/RingBuffer.h>
#include <Core/DataLink/Packet.h>

class PacketProtocol
{
private:
	RingBuffer<char, tttConfig_MAX_RECV_PACKET_SIZE> receiveBuffer;
	uint32_t bytesReceived;
	bool isComplete;
private:
	bool isValueStartSymbol(char value);
	bool isValueEscaped(char value);

public:
	PacketProtocol();

	void process(char value);
	bool isPacketComplete();

	bool getPacket(packet_t& packet);
};

#endif /* CORE_DATALINK_PACKETPROTOCOL_H_ */
