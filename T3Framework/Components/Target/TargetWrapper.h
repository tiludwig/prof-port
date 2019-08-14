/*
 * Target.h
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#ifndef TARGET_H_
#define TARGET_H_

#include <stdint.h>

#include "../../../T3Framework/Core/Communicator/Packet.h"

typedef uint32_t TaskHandle_t;

/*
 * Name:		Target
 *
 * Purpose: 	Provides an interface to be used when implementing new profiling
 * 				target applications. The profiling module will control the target
 * 				through this interface.
 *
 * Implements:	Must implement the ICommandable interface, which is implemented
 * 				by Commandable. Commandable provides a static buffer of configurable
 * 				size.
 */
class TargetWrapper
{
public:

	virtual ~TargetWrapper()
	{
	}

	/*
	 * Name:	getTaskHandle
	 *
	 * Purpose: Gets the FreeRTOS task handle of the wrapped task.
	 */
	virtual TaskHandle_t getTaskHandle() = 0;

	virtual const char* getName() = 0;

	/*
	 * Name:	wrapTask
	 *
	 * Purpose: Wraps the FreeRTOS task in a profilable task.
	 */
	virtual void wrapTask(const char* taskname) = 0;

	/*
	 * Name:	initialize
	 *
	 * Purpose: Initializes the target wrapper. This is called by the profile
	 * 			prior to profiling to allow the target class to do some specific
	 * 			initialization.
	 */
	virtual void initialize() = 0;

	/*
	 * Name:	startProcessCycle
	 *
	 * Purpose: Starts the processing cycle of the target application. Because each
	 * 			target might differ in the way they execute, the actual implementation
	 * 			is up to the implementor.
	 */
	virtual void startProcessCycle() = 0;

	/*
	 * Name:	waitForCycleToEnd
	 *
	 * Purpose: Waits for the processing cycle to end. Because each target might differ
	 * 			in the way they execute, the actual implementation is up to the implementor.
	 *
	 * 			After this function call returns, the profiler will record the execution time.
	 */
	virtual void waitForCycleToEnd() = 0;

	/*
	 * Name:	acceptPacket
	 *
	 * Purpose: Accepts a data packet received from the communication link interface. Processing
	 * 			of the packet's content is implementation defined.
	 */
	virtual void acceptPacket(packet_t& packet) = 0;
};

#endif /* TARGET_H_ */
