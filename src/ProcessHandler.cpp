//
// Created by peau_c on 4/26/17.
//

#include <network/Server.hpp>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <tools/Logger.hpp>
#include "ProcessHandler.hpp"


plazza::ProcessHandler::ProcessHandler(size_t numberOfThreads, char *string)
		: server(MAX_NUMBER_OF_CLIENT), numberOfThreads(numberOfThreads), fileName(string) {
	server.run();
	server.bind(
			std::bind((&plazza::ProcessHandler::handleNewPackets), this, std::placeholders::_1, std::placeholders::_2));
}

void plazza::ProcessHandler::handleNewPackets(const plazza::network::Packet &packet, size_t idClient) {
    if (packet.statusCode == network::StatusCode::RESULT)
    {
		Logger::getInstance().log(packet.data, Logger::NONE);
		Logger::getInstance().logFile(packet.data, Logger::INFO);
    }
    else if (packet.isThreadCount())
    {
        threadOccupancy.at(idClient) = std::stoul(packet.data);
    }
}

plazza::ProcessHandler::~ProcessHandler() {

}

size_t plazza::ProcessHandler::getRemainingSize() const {
	size_t ret = 0;
	
	for (size_t i = 0; i < threadOccupancy.size(); ++i) {
		ret += threadOccupancy.at(i);
	}
	return (ret);
}

size_t plazza::ProcessHandler::getLeastBusyThread() const {
	size_t min = threadOccupancy[0];
	size_t ret = 0;
	
	for (size_t i = 0; i < threadOccupancy.size(); i++) {
		if (min < threadOccupancy.at(i)) {
			min = threadOccupancy.at(i);
			ret = i;
		}
	}
	
	return (ret);
}

void plazza::ProcessHandler::feed(const std::vector<plazza::command> &commands) {
	if (server.getCurrentNumberOfClient() != threadOccupancy.size()) {
		threadOccupancy = std::vector<size_t>(server.getCurrentNumberOfClient());
		for (size_t i = 0; i < threadOccupancy.size(); i++) {
			threadOccupancy[i] = 0;
		}
	}
	while (getRemainingSize() < commands.size()) {
		spawnANewProcess();
		threadOccupancy.push_back(numberOfThreads);
		sleep(1);
	}
	for(auto it = commands.begin(); it < commands.end(); it++) {
		size_t idLeastBusyThread = getLeastBusyThread();
		sendTask(*it, idLeastBusyThread);
		threadOccupancy.at((static_cast<unsigned long>(it - commands.begin()))) -= 1;
		getRemainingSize();
	}
}

void plazza::ProcessHandler::sendTask(const plazza::command command, long clientNumber) {
	network::Packet packet;
	
	if (server.getClientList().empty() || (unsigned long)clientNumber > server.getCurrentNumberOfClient()) {
		return;
	}
	packet.data = command.toString();
	packet.statusCode = network::StatusCode::TASK;
	server.send(packet, server.getClientList().at((unsigned long) clientNumber));
}

void plazza::ProcessHandler::queryProcessOccupancy() {
	for(auto it = server.getClientList().begin(); it < server.getClientList().end(); it++) {
		server.send(network::Packet::QUERY, *it);
	}
}

void plazza::ProcessHandler::spawnANewProcess() {
	pid_t tmp;
	
	if ((tmp = fork()) == -1)
		throw std::runtime_error("Impossible to fork(), cannot spawn a new process");
	if (tmp == 0) {
		char **tab = new char *[6];
		tab[0] = strdup(fileName);
		tab[1] = strdup(std::to_string(numberOfThreads).c_str());
		tab[2] = strdup("-c");
		tab[3] = strdup("-p");
		tab[4] = strdup(std::to_string(server.getPort()).c_str());
		tab[5] = nullptr;
        if (!tab[0] || !tab[1] || !tab[2] || !tab[3] || !tab[4])
            throw std::bad_alloc();
        execvp(fileName, tab);
	}
	childProcessList.push_back(tmp);
}

bool plazza::ProcessHandler::areProcessesFull() const {
	for(std::size_t i = 0; i < threadOccupancy.size(); ++i) {
		if (threadOccupancy.at(i) != 0)
			return (false);
	}
	return (true);
}

std::vector<size_t> plazza::ProcessHandler::getProcessOccupancy() const {
	return threadOccupancy;
}
