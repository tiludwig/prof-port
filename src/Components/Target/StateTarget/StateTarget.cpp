/*
 * StateTarget.cpp
 *
 *  Created on: 27.03.2019
 *      Author: Tim
 */

#include <Components/Target/StateTarget/StateTarget.h>

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

StateTarget::~StateTarget()
{
	// TODO Auto-generated destructor stub
}

TaskHandle_t StateTarget::getTaskHandle()
{
	return task;
}

void StateTarget::wrapTask(TaskHandle_t task)
{
	this->task = task;
}

void StateTarget::initialize()
{
	extern SemaphoreHandle_t xProfSem;
	if(xProfSem == NULL)
	{
		xProfSem = xSemaphoreCreateBinary();
		xSemaphoreTake(xProfSem, portMAX_DELAY);
	}
}

void StateTarget::startProcessCycle()
{
	extern SemaphoreHandle_t xProfSem;

	// Signal start to target
	xSemaphoreGive(xProfSem);
}

void StateTarget::waitForCycleToEnd()
{
	vTaskDelay(1000);
}

void StateTarget::accept(IComLink* sender, uint8_t id)
{

}
