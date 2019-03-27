/*
 ******************************************************************************
 File:     main.cpp
 Info:     Generated by Atollic TrueSTUDIO(R) 9.0.0   2019-03-19

 The MIT License (MIT)
 Copyright (c) 2018 STMicroelectronics


 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 ******************************************************************************
 */

/* Includes */
#include "stm32f10x.h"
#include <string.h>
#include <stdlib.h>

#include <Core/CommandReceiver/CommandReceiver.h>
#include <Components/ComLink/SerialLink.h>
#include <Components/Target/Target.h>
#include <Core/Buffer/basic_buffer.h>
#include <Core/Stream/streamreader.h>
#include <Core/Profiler/Profiler.h>

#include <Core/ExecutionTimer/cm3_dwt.h>
#include <stm32f1xx_it.h>

#include <matrix_t.h>

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

TaskHandle_t xProfTask = NULL;

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

class TestTarget: public Target
{
public:
	virtual void initialize()
	{
	}

	virtual void startProcessCycle()
	{
	}
	virtual void waitForCycleToEnd()
	{
	}

	virtual void accept(IComLink* sender, uint8_t id)
	{
		// i've received something, check out my buffer via streamreader
		streamreader reader(buffer);
		auto iterations = reader.read<uint32_t>();

		char msg[] = "[Target] Received a command (pl=";
		unsigned int msglen = strlen(msg);
		sender->write((uint8_t*) msg, msglen);

		char buf[11];
		itoa(iterations, buf, 10);
		msglen = strlen(buf);
		sender->write((uint8_t*) buf, msglen);
		sender->write((uint8_t*) ")\n", 2);
	}
};

class Application: public Commandable<32>
{
public:
	virtual void initialize()
	{
	}

	virtual void startProcessCycle()
	{
	}
	virtual void waitForCycleToEnd()
	{
	}

	virtual void accept(IComLink* sender, uint8_t id)
	{
		// i've received something, check out my buffer via streamreader

		char msg[] = "[App] Received a command\n";
		unsigned int msglen = strlen(msg);
		sender->write((uint8_t*) msg, msglen);
	}
};

SemaphoreHandle_t xProfSem = NULL;
volatile int state[4];

void propagate_state(volatile int* state, int dt, int update_mat[4][4])
{

	update_mat[0][2] = dt;
	update_mat[1][3] = dt;

	for (int row = 0; row < 4; row++)
	{
		int tempstate = 0;
		for (int col = 0; col < 4; col++)
		{
			tempstate += update_mat[row][col] * state[col];
		}
		state[row] = tempstate;
	}
}

void uiTask(void* pv)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef ioInit;
	ioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	ioInit.GPIO_Pin = GPIO_Pin_13;
	ioInit.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(GPIOC, &ioInit);

	while (1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		vTaskDelay(100);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		vTaskDelay(950);
	}
}

void idleTask(void* pv)
{
	while (1)
	{

	}
}

/*void usableTask(void *pv)
 {
 state[0] = 0;
 state[1] = 0;
 state[2] = 2;
 state[3] = 1;
 int update_mat[4][4] = { { 1, 0, 100, 0 }, { 0, 1, 0, 100 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };

 while (1)
 {
 if (xSemaphoreTake(xProfSem, portMAX_DELAY) != pdTRUE)
 {
 continue;
 }

 for (int row = 0; row < 4; row++)
 {
 int tempstate = 0;
 for (int col = 0; col < 4; col++)
 {
 tempstate += update_mat[row][col] * state[col];
 }
 state[row] = tempstate;
 }
 }
 }*/

void profilerTask(void* pv)
{
	__asm__ __volatile__("":::"memory");
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	__asm__ __volatile__("":::"memory");
	DWT->CTRL |= DWT_CTRL_CYCCNTENA | DWT_CTRL_CPIEVTENA | DWT_CTRL_LSUEVTENA;
	__asm__ __volatile__("":::"memory");
	DWT->CYCCNT = 0;

	xProfSem = xSemaphoreCreateBinary();

	state[0] = 0;
	state[1] = 0;
	state[2] = 2;
	state[3] = 1;
	int update_mat[4][4] = { { 1, 0, 100, 0 }, { 0, 1, 0, 100 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };

	SerialLink link;
	link.initialize();

	TestTarget target;

	Profiler profiler;
	profiler.setProfilingTarget(&target);

	Application app;

	CommandReceiver receiver;
	receiver.setLink(&link);
	receiver.registerComponent(1, &target);
	receiver.registerComponent(20, &profiler);
	receiver.registerComponent(30, &app);
	char buf[13];
	DWT->CYCCNT = 0;
	while (true)
	{
		//receiver.waitForCommand();

		xSemaphoreGive(xProfSem);
		__DSB();
		__ISB();
		DWT->CYCCNT = 0;
		__asm__ __volatile__("":::"memory");

		/*if (xSemaphoreTake(xProfSem, portMAX_DELAY) == pdTRUE)
		 {
		 for (int row = 0; row < 4; row++)
		 {
		 int tempstate = 0;
		 for (int col = 0; col < 4; col++)
		 {
		 tempstate += update_mat[row][col] * state[col];
		 }
		 state[row] = tempstate;
		 }
		 }*/


		__asm__ __volatile__("":::"memory");
		__DSB();
		uint32_t time = DWT->CYCCNT - 1;

		__asm__ __volatile__("":::"memory");

		itoa(time, buf, 10);
		send_msg(1, buf);
		vTaskDelay(950);

	}
}

void serialTask(void* pv)
{

	SerialLink link;
	link.initialize();
	while (1)
	{
		auto data = link.read();
		link.write(&data, 1);
	}
}

int main()
{
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4);

	xTaskCreate(uiTask, "ui_task", 128, NULL, 1, NULL);
	xTaskCreate(profilerTask, "serial", 512, NULL, 2, NULL);
	//xTaskCreate(usableTask, "target", 128, NULL, 3, &xProfTask);
	xTaskCreate(idleTask, "idle", 128, NULL, 0, NULL);
	xPortStartScheduler();

	while (1)
	{

	}
	return 0;
}
