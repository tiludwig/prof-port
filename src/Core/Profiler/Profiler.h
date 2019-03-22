/*
 * Profiler.h
 *
 *  Created on: 22.03.2019
 *      Author: Tim
 */

#ifndef CORE_PROFILER_PROFILER_H_
#define CORE_PROFILER_PROFILER_H_

#include <Core/CommandReceiver/Commandable.h>
#include <Components/Target/Target.h>

class Profiler : public Commandable<64>
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
