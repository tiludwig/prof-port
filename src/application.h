/*
 * application.h
 *
 *  Created on: 27.03.2019
 *      Author: Tim
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <Core/DataLink/PacketReceiver.h>
#include <Core/Profiler/Profiler.h>
#include <Components/ComLink/SerialLink.h>
#include <Components/Target/StateTarget/StateTarget.h>
#include <string.h>
#include <stdlib.h>
#include <Core/Buffer/buffer.h>

int numOfBlinks;

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

void send_msg(uint8_t id, uint16_t size, const char* payload)
{
	uint8_t lenLSB = size & 0xFF;
	uint8_t lenMSB = (size >> 8) & 0xFF;

	int8_t checksum = id;
	checksum += lenLSB;
	checksum += lenMSB;

	generateStartSymbol();
	putc(id);
	putc(lenLSB);
	putc(lenMSB);

	for (uint16_t i = 0; i < size; i++)
	{
		char value = payload[i];
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

	PacketReceiver receiver;
	receiver.setLink(&link);
	vTaskDelay(1233);

	char buf[13];
	extern int state[4];
	while (1)
	{
		receiver.waitForCommand();
		numOfBlinks = 1;
		auto packet = receiver.getPacket();
		if (packet.id == 10)
		{
			receiver.sendOk(11);
			numOfBlinks = 2;
			uint32_t result = profiler.profile();


			itoa(result, buf, 10);
			send_msg(65, strlen(buf), buf);
			numOfBlinks = 3;
			send_msg(10, 4 * sizeof(int), (char*)state);
			numOfBlinks = 4;
		}
	}
}

#endif /* APPLICATION_H_ */
