/*
 * Profiler.h
 *
 *  Created on: 22.03.2019
 *      Author: Tim
 */

#ifndef CORE_PROFILER_PROFILER_H_
#define CORE_PROFILER_PROFILER_H_

#include <Components/Target/Target.h>
#include <Components/ComLink/IComLink.hpp>

class Profiler
{
private:
	Target* targetTask;
public:
	Profiler();
	virtual ~Profiler();

	void initialize();

	void setProfilingTarget(Target* target);
	uint32_t profile();

	virtual void accept(IComLink* sender, uint8_t id);
};

#endif /* CORE_PROFILER_PROFILER_H_ */
