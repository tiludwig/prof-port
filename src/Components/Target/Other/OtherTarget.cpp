/*
 * OtherTarget.cpp
 *
 *  Created on: 14.04.2019
 *      Author: Tim
 */

#include <Components/Target/Other/OtherTarget.h>
#include <Components/Target/Other/other_target.h>

#include <Core/Reader/PayloadReader.h>

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

OtherTarget::~OtherTarget()
{
}

TaskHandle_t OtherTarget::getTaskHandle()
{
	return task;
}

void OtherTarget::wrapTask(TaskHandle_t task)
{
	this->task = task;
}

void OtherTarget::wrapTask(const char* taskname)
{
	this->task = xTaskGetHandle(taskname);
}

void OtherTarget::initialize()
{
	extern SemaphoreHandle_t xTargetSemaphore;
	if (xTargetSemaphore == NULL)
	{
		xTargetSemaphore = xSemaphoreCreateBinary();
	}
}

void OtherTarget::startProcessCycle()
{
	extern SemaphoreHandle_t xTargetSemaphore;

	// Signal start to target
	xSemaphoreGive(xTargetSemaphore);
}

void OtherTarget::waitForCycleToEnd()
{
}

void OtherTarget::acceptPacket(packet_t& packet)
{
	PayloadReader reader(packet.payload);
	for(int i = 0; i < 256; i++)
	{
		sensorValues[i] = reader.read<int32_t>();
	}
}
