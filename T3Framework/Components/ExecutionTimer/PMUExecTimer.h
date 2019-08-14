/*
 * PMUExecTimer.h
 *
 *  Created on: 24.03.2019
 *      Author: Tim
 */

#ifndef CORE_EXECUTIONTIMER_PMUEXECTIMER_H_
#define CORE_EXECUTIONTIMER_PMUEXECTIMER_H_

#include "../../../Framework/Core/ExecutionTimer/ExecutionTimer.h"

#if defined(USE_FREERTOS)
#include <FreeRTOS.h>
#include <task.h>
#endif

/*
 * Name:	PMUExecTimer
 *
 * Purpose:	Measures the elapsed execution time through the Data-
 * 			watchpoint and trace unit of the cortex-m3.
 *
 */
class PMUExecTimer: public ExecutionTimer
{
private:
	TaskHandle_t targetTask;
public:
	virtual ~PMUExecTimer();

	virtual void initialize(const char*);

	/*
	 * Name:	startMeasurement
	 *
	 * Purpose: Starts the exection time measurement. The actual measurement technique
	 * 			is defined by the implementation.
	 */
	virtual void startMeasurement();

	/*
	 * Name:	getElapsed
	 *
	 * Purpose: Gets the elapsed execution time. The time unit is defined by the imple-
	 * 			mentation.
	 */
	virtual uint32_t getElapsed();

	/*
	 * Name:	stopMeasurement
	 *
	 * Purpose: Stops the measurement of execution time.
	 */
	virtual void stopMeasurement();

};

#endif /* CORE_EXECUTIONTIMER_PMUEXECTIMER_H_ */
