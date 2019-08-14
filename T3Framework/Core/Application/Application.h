/*
 * Application.h
 *
 *  Created on: 30.03.2019
 *      Author: Tim
 */

#ifndef CORE_APPLICATION_APPLICATION_H_
#define CORE_APPLICATION_APPLICATION_H_

#include <stdlib.h>

#include <TTTProfConfig.h>
#include <Core/Analyser/Analyser.h>
#include <Core/Communicator/PacketCommunicator.h>
#include <Components/ExecutionTimer/ExecutionTimer.h>

class ApplicationBuilder;

class Application {
private:
	friend class ApplicationBuilder;
	CommunicationDriver* comdriver;
	TargetWrapper* target;
	Analyser analyser;
	PacketCommunicator communicator;
	uint32_t profilingResult;
private:
	packet_t buildProfilingResultResponse(uint32_t profilingResult);
	void processPacket(packet_t& packet);
	Application();
public:

	void initialize();
	void run();
};

class ApplicationBuilder {
private:
	Application app;
public:
	ApplicationBuilder& withDriver(CommunicationDriver* driver) {
		app.comdriver = driver;
		return *this;
	}

	ApplicationBuilder& withTarget(TargetWrapper* target) {
		app.target = target;
		return *this;
	}

	ApplicationBuilder& withTimingMethod(ExecutionTimer* timer) {
		app.analyser.setTimingMethod(timer);
		return *this;
	}

	Application* build()
	{
		return &app;
	}
};

#endif /* CORE_APPLICATION_APPLICATION_H_ */
