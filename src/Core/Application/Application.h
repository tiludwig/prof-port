/*
 * Application.h
 *
 *  Created on: 30.03.2019
 *      Author: Tim
 */

#ifndef CORE_APPLICATION_APPLICATION_H_
#define CORE_APPLICATION_APPLICATION_H_

#include <Components/driver/communication/SerialDriver.h>
#include <string.h>
#include <stdlib.h>
#include <TTTProfConfig.h>
#include <Core/Communicator/PacketCommunicator.h>
#include <Components/Target/StateTarget/StateTarget.h>
#include <Components/Target/StateTarget/state_propagator.h>
#include <Components/Target/Other/OtherTarget.h>
#include <Core/Analyser/Analyser.h>

class Application
{
private:
	CommunicationDriver* link;
	Target* target;
	Analyser profiler;
	PacketCommunicator communicator;
	unsigned int resultBuffer[5];
private:
	packet_t buildProfilingResultResponse(uint32_t profilingResult);
	void processPacket(packet_t& packet);
public:
	Application();
	void initialize(CommunicationDriver& comlink, Target& profTarget);
	void run();

};

#endif /* CORE_APPLICATION_APPLICATION_H_ */
