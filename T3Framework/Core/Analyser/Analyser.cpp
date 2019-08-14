/*
 * Profiler.cpp
 *
 *  Created on: 22.03.2019
 *      Author: Tim
 */

#include "Analyser.h"
#include <Core/Reader/PayloadReader.h>
#include <TTTProfConfig.h>

Analyser::Analyser()
{

}

Analyser::~Analyser()
{

}

void Analyser::initialize()
{

}

void Analyser::setTimingMethod(ExecutionTimer* timer)
{
	this->timer = timer;
}

void Analyser::setProfilingTarget(TargetWrapper* target)
{
	targetTask = target;
	timer->initialize(target->getTaskName());
}

uint32_t Analyser::profile()
{
	timer->startMeasurement();
	__asm__ __volatile__("":::"memory");
	targetTask->startProcessCycle();
	targetTask->waitForCycleToEnd();
	__asm__ __volatile__("":::"memory");

	uint32_t time = timer->getElapsed() - 1;
	timer->stopMeasurement();
	__asm__ __volatile__("":::"memory");
	return time;
}

void Analyser::acceptPacket(packet_t& packet)
{
	PayloadReader reader(packet.payload);
	// extract taskname
	char taskName[tttConfigMAX_TASK_NAME_LEN];
	reader.readString(taskName);
	// set taskname
	targetTask->wrapTask(taskName);
}
