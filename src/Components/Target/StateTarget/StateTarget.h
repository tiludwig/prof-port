/*
 * StateTarget.h
 *
 *  Created on: 27.03.2019
 *      Author: Tim
 */

#ifndef COMPONENTS_TARGET_STATETARGET_STATETARGET_H_
#define COMPONENTS_TARGET_STATETARGET_STATETARGET_H_

#include "../Target.h"
#include <Components/ComLink/IComLink.hpp>

class StateTarget: public Target
{
private:
	TaskHandle_t task;
public:
	virtual ~StateTarget();

	/*
	 * Name:	getTaskHandle
	 *
	 * Purpose: Gets the FreeRTOS task handle of the wrapped task.
	 */
	virtual TaskHandle_t getTaskHandle();

	/*
	 * Name:	wrapTask
	 *
	 * Purpose: Wraps the FreeRTOS task in a profilable task.
	 */
	virtual void wrapTask(TaskHandle_t task);

	/*
	 * Name:	initialize
	 *
	 * Purpose: Initializes the state target. This is called by the profile
	 * 			prior to profiling to allow the target class to do some specific
	 * 			initialization.
	 */
	virtual void initialize();

	/*
	 * Name:	startProcessCycle
	 *
	 * Purpose: Starts the processing cycle of the target application. Because each
	 * 			target might differ in the way they execute, the actual implementation
	 * 			is up to the implementor.
	 */
	virtual void startProcessCycle();

	/*
	 * Name:	waitForCycleToEnd
	 *
	 * Purpose: Waits for the processing cycle to end. Because each target might differ
	 * 			in the way they execute, the actual implementation is up to the implementor.
	 *
	 * 			After this function call returns, the profiler will record the execution time.
	 */
	virtual void waitForCycleToEnd();

	/*
	 * Name:	acceptPacket
	 *
	 * Purpose: Accepts a data packet received from the communication link interface. Processing
	 * 			of the packet's content is implementation defined.
	 */
	virtual void acceptPacket(packet_t& packet);
};

#endif /* COMPONENTS_TARGET_STATETARGET_STATETARGET_H_ */
