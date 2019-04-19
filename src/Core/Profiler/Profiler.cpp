/*
 * Profiler.cpp
 *
 *  Created on: 22.03.2019
 *      Author: Tim
 */

#include <stm32f10x.h>
#include <TTTProfConfig.h>
#include <Core/ExecutionTimer/cm3_dwt.h>
#include <Core/Profiler/Profiler.h>
#include <Components/ComLink/SerialLink.h>
#include <Core/ExecutionTimer/PMUExecTimer.h>
#include <Core/Reader/PayloadReader.h>


volatile uint32_t bProfilingPaused;
Profiler::Profiler()
{

}

Profiler::~Profiler()
{

}

void Profiler::initialize()
{

}

void Profiler::setProfilingTarget(Target* target)
{
	targetTask = target;
	timer.initializeWithTask(targetTask->getTaskHandle());
}

uint32_t Profiler::profile()
{
	timer.startMeasurement();
	__asm__ __volatile__("":::"memory");
	targetTask->startProcessCycle();
	targetTask->waitForCycleToEnd();
	__asm__ __volatile__("":::"memory");
	__DSB();

	uint32_t time = timer.getElapsed() - 1;
	timer.stopMeasurement();
	__asm__ __volatile__("":::"memory");
	return time;
}

void Profiler::acceptPacket(packet_t& packet)
{
	PayloadReader reader(packet.payload);
	// extract taskname
	char taskName[tttConfigMAX_TASK_NAME_LEN];
	reader.readString(taskName);
	// set taskname
	targetTask->wrapTask(taskName);
}

