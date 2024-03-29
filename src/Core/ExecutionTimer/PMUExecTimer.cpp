/*
 * PMUExecTimer.cpp
 *
 *  Created on: 24.03.2019
 *      Author: Tim
 */

#include <Core/ExecutionTimer/PMUExecTimer.h>
#include <stm32f10x.h>
#include <Core/ExecutionTimer/cm3_dwt.h>

#include <FreeRTOS.h>
#include <task.h>

volatile uint32_t cycleCounter;

PMUExecTimer::~PMUExecTimer()
{
}

void PMUExecTimer::initialize(const char* taskname)
{
	targetTask = xTaskGetHandle(taskname);
}

/*
 * Start the cycle counter
 */
void PMUExecTimer::startMeasurement()
{
	extern TaskHandle_t xProfilingTask;

	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	//DWT->CTRL = ;

	xProfilingTask = targetTask;
	DWT->CYCCNT = 0;
	cycleCounter = 0;
}

/*
 * Get the elapses cycles.
 */
uint32_t PMUExecTimer::getElapsed()
{
	return DWT->CYCCNT;
}

/*
 * Stops the cycle counter
 */
void PMUExecTimer::stopMeasurement()
{
	extern TaskHandle_t xProfilingTask;
	xProfilingTask = NULL;
	DWT->CTRL &= ~DWT_CTRL_CYCCNTENA;
	CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;
}
