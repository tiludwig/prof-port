/*
 * Profiler.h
 *
 *  Created on: 22.03.2019
 *      Author: Tim
 */

#ifndef CORE_ANALYSER_ANALYSER_H_
#define CORE_ANALYSER_ANALYSER_H_

#include <Components/driver/communication/CommunicationDriver.hpp>
#include <Components/Target/TargetWrapper.h>
#include <Components/ExecutionTimer/ExecutionTimer.h>

class Analyser
{
private:
	ExecutionTimer* timer;
	TargetWrapper* targetTask;
public:
	Analyser();
	virtual ~Analyser();

	void initialize();

	void setTimingMethod(ExecutionTimer* timer);
	void setProfilingTarget(TargetWrapper* target);
	uint32_t profile();

	void acceptPacket(packet_t& packet);
};

#endif /* CORE_ANALYSER_ANALYSER_H_ */
