/*
 * Application.cpp
 *
 *  Created on: 30.03.2019
 *      Author: Tim
 */

#include <Core/Application/Application.h>

Application::Application()
		: communicator(nullptr)
{
	link = nullptr;
	target = nullptr;
}

void Application::initialize(CommunicationDriver& comlink, TargetWrapper& profTarget)
{
	this->link = &comlink;
	this->target = &profTarget;

	link->initialize();
	target->initialize();
	profiler.setProfilingTarget(target);
	communicator.setComLink(link);
}

void Application::run()
{
	while (1)
	{
		auto packet = communicator.waitForRequest();
		processPacket(packet);
	}
}

packet_t Application::buildProfilingResultResponse(uint32_t profilingResult)
{
	resultBuffer[0] = profilingResult;
	resultBuffer[1] = state[0];
	resultBuffer[2] = state[1];
	resultBuffer[3] = state[2];
	resultBuffer[4] = state[3];

	packet_t packet;
	packet.id = 65;
	packet.size.value = 5 * sizeof(int);
	packet.payload = (char*) resultBuffer;
	return packet;
}

void Application::processPacket(packet_t& packet)
{
	if (packet.id == tttConfig_COM_ID_APP)
	{
		uint32_t result = profiler.profile();
		auto response = buildProfilingResultResponse(result);
		communicator.sendResponse(response);
	}
	if (packet.id == tttConfig_COM_ID_PROFILER)
	{
		profiler.acceptPacket(packet);

		packet_t packetOk = { 11, 2, (char*) "Ok" };
		communicator.sendResponse(packetOk);
	}
	else if (packet.id == tttConfig_COM_ID_TARGET)
	{
		target->acceptPacket(packet);

		packet_t packetOk = { 11, 2, (char*) "Ok" };
		communicator.sendResponse(packetOk);
	}
}
