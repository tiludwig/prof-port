/*
 * PMUExecTimer.cpp
 *
 *  Created on: 24.03.2019
 *      Author: Tim
 */

#include <Core/ExecutionTimer/PMUExecTimer.h>
#include <stm32f10x.h>
#include <Core/ExecutionTimer/cm3_dwt.h>

PMUExecTimer::~PMUExecTimer()
{
}

/*
 * Start the cycle counter
 */
void startMeasurement()
{
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL = DWT_CTRL_CYCCNTENA;
	DWT->CYCCNT = 0;
}

/*
 * Get the elapses cycles.
 */
uint32_t getElapsed()
{
	return DWT->CYCCNT;
}

/*
 * Stops the cycle counter
 */
void stopMeasurement()
{

	DWT->CTRL &= ~DWT_CTRL_CYCCNTENA;
	CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;
}
