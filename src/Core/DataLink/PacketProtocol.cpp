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
	packet.size.raw.lsb = static_cast<uint8_t>(receiveBuffer.read());
	packet.size.raw.msb = (receiveBuffer.read());
	packet.payload = receiveBuffer.getCurrentItemAddress();
	receiveBuffer.skip(packet.size.value);
	char checksum = receiveBuffer.read();
	if(checksum != 0)
		return false;
	return true;
}
