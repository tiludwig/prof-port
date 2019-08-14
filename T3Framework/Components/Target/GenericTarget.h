/*
 * Generic Target
 *
 * This file contains an empty implementation of the
 * TargetWrapper interface with comments.
 */

#ifndef T3FRAMEWORK_COMPONENTS_TARGET_GENERICTARGET_H_
#define T3FRAMEWORK_COMPONENTS_TARGET_GENERICTARGET_H_

#include "TargetWrapper.h"

class GenericTarget : public TargetWrapper {
private:
	const char* taskName;
public:
	GenericTarget();
	virtual ~GenericTarget();
	/*
	 * Name:	getTaskName
	 *
	 * Purpose: Gets the name of the wrapped task
	 */
	virtual const char* getTaskName();

	/*
	 * Name:	wrapTask
	 *
	 * Purpose: Wraps the task to be profiled into a analyzable task
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

#endif /* T3FRAMEWORK_COMPONENTS_TARGET_GENERICTARGET_H_ */
