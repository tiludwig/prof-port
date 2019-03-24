/*
 * Target.h
 *
 *  Created on: 20.03.2019
 *      Author: Tim
 */

#ifndef TARGET_H_
#define TARGET_H_

#include <stdint.h>
#include <Core/CommandReceiver/Commandable.h>

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
class Target: public Commandable<128>
{
public:
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
};

#endif /* TARGET_H_ */
