/*
 * Packet.h
 *
 *  Created on: 28.03.2019
 *      Author: Tim
 */

#ifndef CORE_DATALINK_PACKET_H_
#define CORE_DATALINK_PACKET_H_

#include <stdint.h>

struct packet_t
{
	uint8_t id;
	uint16_t size;
	char* payload;
	int8_t checksum;
};

class Packet
{
private:

};

#endif /* CORE_DATALINK_PACKET_H_ */
