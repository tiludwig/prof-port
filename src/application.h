/*
 * application.h
 *
 *  Created on: 27.03.2019
 *      Author: Tim
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <Core/CommandReceiver/CommandReceiver.h>
#include <Core/Profiler/Profiler.h>
#include <Components/ComLink/SerialLink.h>
#include <Components/Target/StateTarget/StateTarget.h>
#include <string.h>
#include <stdlib.h>
#include <Core/Buffer/buffer.h>

struct packet_t
{
	uint8_t id;
	uint16_t size;
	buffer_t<char> payload;
	int8_t checksum;
};

class packet_writer
{
private:
	packet_t& packet;

public:
	packet_writer(packet_t& packet)
			: packet(packet)
	{

	}

	template<class UserType>
	void write(UserType& value)
	{
		if (sizeof(UserType) == 1)
		{
			packet.payload.push_back(value);
			return;
		}
		for (unsigned int i = 0; i < sizeof(UserType); i++)
		{
			uint8_t temp = (value >> 8 * i) & 0xFF;
			packet.payload.push_back(temp);
		}
	}

	void write(const char* value)
	{
		while(*value != '\0')
		{
			packet.payload.push_back(*const_cast<char*>(value++));
		}
	}
};

void putc(char value)
{
	if (value == '?' || value == '#')
	{
		USART_SendData(USART1, '?');
		value = value ^ 0x20;

		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
			;
	}
	USART_SendData(USART1, value);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		;
}

void generateStartSymbol()
{
	USART_SendData(USART1, '#');

	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		;
}

void send_msg(uint8_t id, const char* msg)
{

	packet_t packet;


	uint16_t len = static_cast<uint16_t>(strlen(msg));
	uint8_t lenLSB = len & 0xFF;
	uint8_t lenMSB = (len >> 8) & 0xFF;

	int8_t checksum = id;
	checksum += lenLSB;
	checksum += lenMSB;

	generateStartSymbol();
	putc(id);
	putc(lenLSB);
	putc(lenMSB);

	while (*msg != '\0')
	{
		char value = *msg++;
		checksum += value;
		putc(value);
	}

	checksum = -checksum;
	putc(checksum);
}

void appTask(void* pv)
{
	extern TaskHandle_t xProfTask;

	SerialLink link;
	link.initialize();

	StateTarget target;
	target.wrapTask(xProfTask);

	Profiler profiler;
	profiler.setProfilingTarget(&target);

	CommandReceiver receiver;
	receiver.setLink(&link);
	receiver.registerComponent(1, &target);
	receiver.registerComponent(20, &profiler);

	char buf[13];
	while (1)
	{
		uint32_t result = profiler.profile();

		itoa(result, buf, 10);
		send_msg(65, buf);
		vTaskDelay(1000);
	}
}

#endif /* APPLICATION_H_ */