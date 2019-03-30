/*
 * PacketCommunicator.h
 *
 *  Created on: 29.03.2019
 *      Author: Tim
 */

#ifndef CORE_COMMUNICATOR_PACKETCOMMUNICATOR_H_
#define CORE_COMMUNICATOR_PACKETCOMMUNICATOR_H_

#include <Components/ComLink/IComLink.hpp>
#include <Core/Communicator/PacketProtocol.h>
#include <Core/Communicator/Packet.h>

class PacketCommunicator
{
private:
	IComLink* comDriver;
	PacketProtocol protocol;
private:
	void sendStartSymbol();
	void send(char* buffer, uint16_t size);
	void sendByte(char value);
public:
	PacketCommunicator(IComLink* link);

	void setComLink(IComLink* link);

	int8_t calculateChecksum(packet_t& packet);
	void sendPacket(packet_t& packet);
	void receivePacket(packet_t& packet);


	packet_t waitForRequest();
	void sendResponse(packet_t& response);
};

#endif /* CORE_COMMUNICATOR_PACKETCOMMUNICATOR_H_ */
