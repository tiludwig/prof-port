/*
 * SerialLink.cpp
 *
 *  Created on: 19.03.2019
 *      Author: Tim
 */

#include <comlink/SerialLink.h>
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>

SerialLink::~SerialLink()
{

}

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
	usartInit.USART_BaudRate = 9600;
	usartInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usartInit.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	usartInit.USART_Parity = USART_Parity_No;
	usartInit.USART_StopBits = USART_StopBits_1;
	usartInit.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usartInit);

	USART_Cmd(USART1, ENABLE);
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//NVIC_EnableIRQ(USART1_IRQn);
	return true;
}

void SerialLink::write(uint8_t* data, uint32_t count)
{
	for (uint32_t i = 0; i < count; i++)
	{
		USART_SendData(USART1, data[i]);

		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
			;
	}
}

uint8_t SerialLink::read()
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
		;

	return (USART1->DR & 0xFF);
}
