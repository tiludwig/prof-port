/*
 * Profiler.cpp
 *
 *  Created on: 22.03.2019
 *      Author: Tim
 */

#include <string.h>
#include <stm32f10x.h>
#include <Core/ExecutionTimer/cm3_dwt.h>
#include <Core/Profiler/Profiler.h>
#include <Components/ComLink/SerialLink.h>
#include <Core/ExecutionTimer/PMUExecTimer.h>



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

void Profiler::accept(IComLink* sender, uint8_t id)
{
	char msg[] = "[Profiler] Received new command\n";
	auto len = strlen(msg);
	sender->write((uint8_t*) msg, len);
}

