/*
 * ExecutionTimer.h
 *
 *  Created on: 24.03.2019
 *      Author: Tim
 */

#ifndef CORE_PROFILER_EXECUTIONTIMER_H_
#define CORE_PROFILER_EXECUTIONTIMER_H_

#include <stdint.h>

/*
 * Name:	ExecutionTimer
 *
 * Purpose: Provides an interface for measuring the elapsed execution time between
 * 			calls to 'startMeasurement' and 'getElapsed'. The underlying method to
 * 			measure the execution time, as well as the execution time unit is im-
 * 			plementation defined.
 *
 */
class ExecutionTimer
{
public:
	virtual ~ExecutionTimer() {}

	/*
	 * Name:		initialize
	 *
	 * Purpose:		Initializes the execution timer.
	 *
	 * Arguments:	params Generic initialization parameters to the execution timer.
	 * 					   This could be a pid/tid, a taskhandle, a taskname, etc.
	 */
	virtual void initialize(void* params) = 0;

	/*
	 * Name:	startMeasurement
	 *
	 * Purpose: Starts the execution time measurement. This function is called by the
	 * 			analyzer module prior to starting the process cycle of the target. The
	 * 			actual measurement technique is defined by the implementation.
	 */
	virtual void startMeasurement() = 0;

	/*
	 * Name:	getElapsed
	 *
	 * Purpose: Gets the elapsed execution time. This function is called by the
	 * 			analyzer module after the process cycle of the target has ended.
	 * 			The time unit is defined by the implementation.
	 */
	virtual uint32_t getElapsed() = 0;

	/*
	 * Name:	stopMeasurement
	 *
	 * Purpose: Stops the measurement of execution time.
	 */
	virtual void stopMeasurement() = 0;
};

#endif /* CORE_PROFILER_EXECUTIONTIMER_H_ */
