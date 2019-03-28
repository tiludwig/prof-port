/*
 * PacketProtocol.cpp
 *
 *  Created on: 28.03.2019
 *      Author: Tim
 */

#include <Core/DataLink/PacketProtocol.h>

PacketProtocol::PacketProtocol()
{

}

void PacketProtocol::process(char value)
{

}


bool PacketProtocol::isPacketComplete()
{
	return isComplete;
}

bool PacketProtocol::getPacket(packet_t& packet)
{
	packet.id = static_cast<uint8_t>(receiveBuffer.read());
	packet.size = static_cast<uint8_t>(receiveBuffer.read());
	packet.size |= (static_cast<uint16_t>(receiveBuffer.read()) << 8);
	packet.payload = receiveBuffer.getCurrentItemAddress();
	receiveBuffer.skip(packet.size);
	packet.checksum = receiveBuffer.read();
	return true;
}
