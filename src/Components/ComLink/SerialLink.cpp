/*
 * SerialLink.cpp
 *
 *  Created on: 19.03.2019
 *      Author: Tim
 */

#include <Components/ComLink/SerialLink.h>
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>
#include <FreeRTOS.h>
#include <semphr.h>

#define BUFFER_SIZE		32
#define BUFFER_MASK		(BUFFER_SIZE - 1)

volatile char ringbuffer[BUFFER_SIZE];
volatile uint32_t head;
volatile uint32_t tail;

SemaphoreHandle_t xSemaphore = NULL;

bool rb_empty()
{
	return (head == tail);
}

uint32_t rb_size()
{
	return (tail - head);
}

bool rb_full()
{
	return (rb_size() == BUFFER_SIZE);
}

void rb_push(char value)
{
	if (rb_full())
		return;

	// compute index
	uint32_t writeIndex = (tail++) & BUFFER_MASK;
	ringbuffer[writeIndex] = value;
}

char rb_read()
{
	if (rb_empty())
		return -1;

	uint32_t readIndex = (head++) & BUFFER_MASK;
	return ringbuffer[readIndex];
}

extern "C" void USART1_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		rb_push(USART_ReceiveData(USART1));
		xSemaphoreGiveFromISR(xSemaphore, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

SerialLink::~SerialLink()
{

}

/*
 * Initializes the UART peripheral and its corresponding IO's
 */
bool SerialLink::initialize()
{
	RCC_APB2PeriphClockCmd(
	RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitTypeDef gpioInit;

	// Init TX as AF PP
	gpioInit.GPIO_Pin = GPIO_Pin_9;
	gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInit);

	// Init RX as Input
	gpioInit.GPIO_Pin = GPIO_Pin_10;
	gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInit);

	USART_InitTypeDef usartInit;
	usartInit.USART_BaudRate = 119200;
	usartInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usartInit.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	usartInit.USART_Parity = USART_Parity_No;
	usartInit.USART_StopBits = USART_StopBits_1;
	usartInit.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usartInit);

	/* Enable the USART3 Interrupt */
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 200;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1, ENABLE);

	xSemaphore = xSemaphoreCreateBinary();
	return true;
}

/*
 * write n bytes to the UART
 */
void SerialLink::write(const uint8_t* data, uint32_t count)
{
	for (uint32_t i = 0; i < count; i++)
	{
		USART_SendData(USART1, data[i]);

		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
			;
	}
}

/*
 * read a single byte from UART
 */
uint8_t SerialLink::read()
{
	// check if data is available
	if(rb_size() == 0)
	{
		// No - wait for data to become available
		xSemaphoreTake(xSemaphore, portMAX_DELAY);
	}

	// Data was available or has become available
	return rb_read();
}
