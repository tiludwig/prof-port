/*
 * Profiler.h
 *
 *  Created on: 22.03.2019
 *      Author: Tim
 */

#ifndef CORE_ANALYSER_ANALYSER_H_
#define CORE_ANALYSER_ANALYSER_H_

#include <Components/driver/communication/CommunicationDriver.hpp>
#include <Components/Target/Target.h>
#include <Core/ExecutionTimer/PMUExecTimer.h>

class Analyser
{
private:
	PMUExecTimer timer;
	Target* targetTask;
public:
	Analyser();
	virtual ~Analyser();

	void initialize();

	void setProfilingTarget(Target* target);
	uint32_t profile();

	void acceptPacket(packet_t& packet);
};

#endif /* CORE_ANALYSER_ANALYSER_H_ */
