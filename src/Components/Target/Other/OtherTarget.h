/*
 * OtherTarget.h
 *
 *  Created on: 14.04.2019
 *      Author: Tim
 */

#ifndef COMPONENTS_TARGET_OTHER_OTHERTARGET_H_
#define COMPONENTS_TARGET_OTHER_OTHERTARGET_H_

#include <Components/driver/communication/CommunicationDriver.hpp>
#include <Components/Target/TargetWrapper.h>

class OtherTarget: public TargetWrapper
{
private:
	const char* name;
	TaskHandle_t task;
public:
	virtual ~OtherTarget();

	/*
	 * Name:	getTaskHandle
	 *
	 * Purpose: Gets the FreeRTOS task handle of the wrapped task.
	 */
	virtual TaskHandle_t getTaskHandle();

	virtual const char* getName();

	/*
	 * Name:	wrapTask
	 *
	 * Purpose: Wraps the FreeRTOS task in a profilable task.
	 */
	virtual void wrapTask(const char* taskname);

	/*
	 * Name:	initialize
	 *
	 * Purpose: Initializes the target wrapper. This is called by the profile
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

#endif /* COMPONENTS_TARGET_OTHER_OTHERTARGET_H_ */
