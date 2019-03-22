/*
 * Profiler.cpp
 *
 *  Created on: 22.03.2019
 *      Author: Tim
 */

#include <string.h>
#include <Core/Profiler/Profiler.h>

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
}

uint32_t Profiler::profile()
{
	return 0;
}

void Profiler::accept(IComLink* sender, uint8_t id)
{
	char msg[] = "[Profiler] yOu WaNt SuM dAtA??\n";
	auto len = strlen(msg);
	sender->write((uint8_t*)msg, len);
}

