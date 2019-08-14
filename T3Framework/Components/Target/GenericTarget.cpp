/*
 * GenericTarget.cpp
 *
 *  Created on: Aug 14, 2019
 *      Author: tim
 */

#include <Components/Target/GenericTarget.h>

GenericTarget::GenericTarget()
{
	// Setup class variables
	taskName = nullptr;
}

GenericTarget::~GenericTarget()
{

}

/*
 * Name:	getTaskName
 *
 * Purpose: Gets the name of the wrapped task
 */
const char* GenericTarget::getTaskName()
{
	return taskName;
}

/*
 * Name:	wrapTask
 *
 * Purpose: Wraps the task to be profiled into a analyzable task
 */
void GenericTarget::wrapTask(const char* taskname)
{
	// Save the task name
	this->taskName = taskname;

	// wrap the task. Depending on the task, this could:
	// - query the operation system for the task handle
	// - attach to a running process
	// - prepare to spawn a new process/thread
}

/*
 * Name:	initialize
 *
 * Purpose: Initializes the target wrapper. This is called by the profile
 * 			prior to profiling to allow the target class to do some specific
 * 			initialization.
 */
void GenericTarget::initialize()
{
	// Initializes the target wrapper. This could involve:
	// - create communication channel to talk to the target
	//		- named pipes
	//		- socket connection
	//		- shared memory

	// Depending on the operating system and task this could also:
	// - spawn a new thread for the target
	// - start the target process
}

/*
 * Name:	startProcessCycle
 *
 * Purpose: Starts the processing cycle of the target application. Because each
 * 			target might differ in the way they execute, the actual implementation
 * 			is up to the implementor.
 */
void GenericTarget::startProcessCycle()
{
	// This also depends on the target:
	// - start a command line target with the right args
	// - send values to a target, that waits for values on a port
	// - signal a target (thread) to continue execution
}

/*
 * Name:	waitForCycleToEnd
 *
 * Purpose: Waits for the processing cycle to end. Because each target might differ
 * 			in the way they execute, the actual implementation is up to the implementor.
 *
 * 			After this function call returns, the profiler will record the execution time.
 */
void GenericTarget::waitForCycleToEnd()
{
	// Depending on the target:
	// - wait until an answer is received
	// - continue as soon as this thread continues execution
	// - wait for a certain timespan
}

/*
 * Name: 	acceptPacket
 *
 * Purpose: Accepts and processes a packet from the upper layers.
 *
 */
void GenericTarget::acceptPacket(packet_t& packet)
{
	// This is a packet sent from the command line interface (host)
	// It contains the input to the target:
	// - store the input values for later use
	// - directly send them to the target, because the cycle is triggered
	//   in another way
	// - put them to shared memory (unless the target monitors the sm for
	//   changes)
}
