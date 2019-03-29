/*
 * application.h
 *
 *  Created on: 27.03.2019
 *      Author: Tim
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <Core/Profiler/Profiler.h>
#include <Components/ComLink/SerialLink.h>
#include <Components/Target/StateTarget/StateTarget.h>
#include <Core/Buffer/buffer_t.h>
#include <string.h>
#include <stdlib.h>
#include <Core/Communicator/PacketCommunicator.h>

int numOfBlinks;


extern void shownumber(int num);

void appTask(void* pv)
{
	extern TaskHandle_t xProfTask;

	SerialLink link;
	link.initialize();

	StateTarget target;
	target.wrapTask(xProfTask);
	target.initialize();

	Profiler profiler;
	profiler.setProfilingTarget(&target);

	PacketCommunicator communicator(&link);
	packet_t packetOk = {11, 2, (char*)"Ok"};

	char buf[13];
	extern int state[4];
	numOfBlinks = 1;
	while (1)

	{numOfBlinks = 1;
		auto packet = communicator.waitForRequest();
		numOfBlinks = 2;
		if (packet.id == 10)
		{
			uint32_t result = profiler.profile();

			unsigned int buf[5];
			buf[0] = result;
			buf[1] = state[0];
			buf[2] = state[1];
			buf[3] = state[2];
			buf[4] = state[3];
			packet_t response = {65,5*sizeof(int), (char*)buf};
			communicator.sendResponse(response);
			numOfBlinks = 4;
		}
		else if(packet.id == 20)
		{
			target.acceptPacket(packet);
			communicator.sendResponse(packetOk);
			numOfBlinks = 6;
		}
	}
}

#endif /* APPLICATION_H_ */
