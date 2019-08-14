/**
 *
 * File header
 *
 */
#include "TTTProfConfig.h"
#include <Core/Application/Application.h>

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
void frameworkEntryPoint(CommunicationDriver* comDriver, TargetWrapper* target, ExecutionTimer* timer) {
	// Build the application
	ApplicationBuilder appBuilder;
	appBuilder.withDriver(comDriver);
	appBuilder.withTarget(target);
	appBuilder.withTimingMethod(timer);
	Application* app = appBuilder.build();

	// Initialize the application
	app->initialize();
	// Run the application
	app->run();

	// This point should never be reached.
	while (1) {
		continue;
	}
}
