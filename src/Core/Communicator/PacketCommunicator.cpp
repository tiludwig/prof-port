/*
 * PacketCommunicator.cpp
 *
 *  Created on: 29.03.2019
 *      Author: Tim
 */

#include <Core/Communicator/PacketCommunicator.h>

PacketCommunicator::PacketCommunicator(CommunicationDriver* link)
{
	comDriver = link;
}

void PacketCommunicator::setDriver(CommunicationDriver* link)
{
	comDriver = link;
}

int8_t PacketCommunicator::calculateChecksum(packet_t& packet)
{
	int8_t checksum = packet.id;
	checksum += packet.size.raw.lsb;
	checksum += packet.size.raw.msb;

	for (uint16_t i = 0; i < packet.size.value; i++)
	{
		checksum += packet.payload[i];
	}

	return -checksum;
}

void PacketCommunicator::sendStartSymbol()
{
	comDriver->write((uint8_t*) "#", 1);
}

void PacketCommunicator::send(char* buffer, uint16_t size)
{

	for (uint16_t i = 0; i < size; i++)
	{
		sendByte(buffer[i]);
	}

}

void PacketCommunicator::sendByte(char value)
{
	if (value == '?' || value == '#')
	{
		comDriver->write((uint8_t*)"?", 1);
		value = value ^ 0x20;
	}
	comDriver->write(reinterpret_cast<uint8_t*>(&value), 1);

}

void PacketCommunicator::sendPacket(packet_t& packet)
{
	int8_t checksum = calculateChecksum(packet);
	sendStartSymbol();
	sendByte(packet.id);
	sendByte(packet.size.raw.lsb);
	sendByte(packet.size.raw.msb);
	send(packet.payload, packet.size.value);
	sendByte(checksum);
}

void PacketCommunicator::receivePacket(packet_t& packet)
{
	while (!protocol.isPacketComplete())
	{
		auto receivedByte = comDriver->read();
		protocol.processByte(receivedByte);
	}

	protocol.getPacket(packet);
}

packet_t PacketCommunicator::waitForRequest()
{
	packet_t packet;
	receivePacket(packet);
	return packet;
}

void PacketCommunicator::sendResponse(packet_t& response)
{
	sendPacket(response);
}
