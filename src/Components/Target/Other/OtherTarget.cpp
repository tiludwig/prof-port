/*
 * OtherTarget.cpp
 *
 *  Created on: 14.04.2019
 *      Author: Tim
 */

#include <Components/Target/Other/other_target.h>
#include <Components/Target/Other/OtherTarget.h>
#include <Core/Reader/PayloadReader.h>

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

extern int32_t unsorted_array[32];

OtherTarget::~OtherTarget() {
}

TaskHandle_t OtherTarget::getTaskHandle() {
	return taskHandle;
}

const char* OtherTarget::getName()
{
	return this->taskName;
}

void OtherTarget::wrapTask(const char* taskname) {
	this->taskName = taskname;
	this->taskHandle = xTaskGetHandle(taskname);
}

void OtherTarget::initialize() {
	extern SemaphoreHandle_t xTargetSemaphore;
	if (xTargetSemaphore == NULL) {
		xTargetSemaphore = xSemaphoreCreateBinary();
	}
}

void OtherTarget::startProcessCycle() {
	// set the task to profile
	extern TaskHandle_t xProfilingTask;
	xProfilingTask = this->taskHandle;

	extern SemaphoreHandle_t xTargetSemaphore;

	// Signal start to target
	xSemaphoreGive(xTargetSemaphore);
}

void OtherTarget::waitForCycleToEnd() {
}

void OtherTarget::acceptPacket(packet_t& packet) {
	PayloadReader reader(packet.payload);
	/*for (int i = 0; i < 32; i++)
	 {
	 unsorted_array[i] = reader.read<int32_t>();
	 }*/
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			array2[i][j] = reader.read<int32_t>();
		}
	}
	/*lengthInfo[0] = reader.read<int32_t>();
	 lengthInfo[1] = reader.read<int32_t>();*/
}
