/*
 * Application.cpp
 *
 *  Created on: 30.03.2019
 *      Author: Tim
 */

#include "../../../T3Framework/Core/Application/Application.h"

Application::Application() :
		communicator(nullptr) {
	comdriver = nullptr;
	target = nullptr;
}

void Application::initialize() {
	comdriver->initialize();
	target->initialize();
	analyser.setProfilingTarget(target);
	communicator.setDriver(comdriver);
}

/*void Application::initialize(CommunicationDriver& comlink,
		TargetWrapper& profTarget) {
	this->comdriver = &comlink;
	this->target = &profTarget;

	comdriver->initialize();
	target->initialize();
	ana
	analyser.setProfilingTarget(target);
	communicator.setDriver(comdriver);
}*/

void Application::run() {
	while (1) {
		auto packet = communicator.waitForRequest();
		processPacket(packet);
	}
}

packet_t Application::buildProfilingResultResponse(uint32_t result) {
	profilingResult = result;

	packet_t packet;
	packet.id = 65;
	packet.size.value = 1 * sizeof(uint32_t);
	packet.payload = (char*) &profilingResult;
	return packet;
}

void Application::processPacket(packet_t& packet) {
	if (packet.id == tttConfig_COM_ID_APP) {
		uint32_t result = analyser.profile();
		auto response = buildProfilingResultResponse(result);
		communicator.sendResponse(response);
	}
	if (packet.id == tttConfig_COM_ID_PROFILER) {
		analyser.acceptPacket(packet);

		packet_t packetOk = { 11, 2, (char*) "Ok" };
		communicator.sendResponse(packetOk);
	} else if (packet.id == tttConfig_COM_ID_TARGET) {
		target->acceptPacket(packet);

		packet_t packetOk = { 11, 2, (char*) "Ok" };
		communicator.sendResponse(packetOk);
	}
}
