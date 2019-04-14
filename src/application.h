/*
 * application.h
 *
 *  Created on: 27.03.2019
 *      Author: Tim
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <Core/Application/Application.h>
#include <Utility/ui-task/ui-task.h>
#include <TTTProfConfig.h>

extern TaskHandle_t xProfilingTask;

void appTask(void* pv)
{
	SerialLink link;

	OtherTarget target;
	target.wrapTask(tttConfig_PROF_TASK_NAME);

	Application app;
	app.initialize(link, target);

	uiSignal(1);
	app.run();

	// We should never get here, but just in case

	while (1)
	{

	}

}

#endif /* APPLICATION_H_ */
