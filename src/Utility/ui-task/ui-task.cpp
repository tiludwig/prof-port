/*
 * ui-task.cpp
 *
 *  Created on: 27.03.2019
 *      Author: Tim
 */

#include "stm32f10x.h"
#include <stm32f1xx_it.h>

#include <FreeRTOS.h>
#include <task.h>

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
