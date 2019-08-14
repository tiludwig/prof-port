
/**
 *
 * File header
 *
 */
#ifndef T3_FRAMEWORK_H_
#define T3_FRAMEWORK_H

#include "../T3Framework/Core/Application/Application.h"

/**
 * Main Function
 *
 * This is the profiler's entry point. Depending on the target system,
 * the main might need to be adjusted to be used as an independent task.
 *
 * @param comDriver A pointer to the communication driver to be used by
 * 					the framework
 * @param target	A pointer to the object that handles target specific
 * 					functions
 * @param timer		A pointer to the execution timer method to be used by
 * 					the framework
 *
 * NOTE: Function does not return
 */
void frameworkEntryPoint(CommunicationDriver* comDriver, TargetWrapper* target, ExecutionTimer* timer);
#endif
