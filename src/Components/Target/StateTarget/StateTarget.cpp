/*
 * StateTarget.cpp
 *
 *  Created on: 27.03.2019
 *      Author: Tim
 */

#include <Components/Target/StateTarget/StateTarget.h>
#include <Core/Reader/PayloadReader.h>
#include "state_propagator.h"

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include <string.h>

extern volatile int accelerations[2];

StateTarget::~StateTarget()
{

}

TaskHandle_t StateTarget::getTaskHandle()
{
	return task;
}

void StateTarget::wrapTask(TaskHandle_t task)
{
	this->task = task;
}

void StateTarget::wrapTask(const char* taskname)
{
	this->task = xTaskGetHandle(taskname);
}

void StateTarget::initialize()
{
	extern SemaphoreHandle_t xProfSem;
	if (xProfSem == NULL)
	{
		xProfSem = xSemaphoreCreateBinary();
		//xSemaphoreTake(xProfSem, portMAX_DELAY);
	}

	accelerations[0] = 0;
	accelerations[1] = 1;
}

void StateTarget::startProcessCycle()
{
	extern SemaphoreHandle_t xProfSem;

	// Signal start to target
	xSemaphoreGive(xProfSem);
}

void StateTarget::waitForCycleToEnd()
{
}

void StateTarget::acceptPacket(packet_t& packet)
{
	PayloadReader reader(packet.payload);
	predictorOdometryInput.type = static_cast<OdometryType_t> (reader.read<int>());
	predictorOdometryInput.acceleration[0] = reader.read<int>();
	predictorOdometryInput.acceleration[1] = reader.read<int>();
}
