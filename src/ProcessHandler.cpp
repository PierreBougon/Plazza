//
// Created by peau_c on 4/26/17.
//

#include <network/Server.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include "ProcessHandler.hpp"


plazza::ProcessHandler::ProcessHandler(size_t numberOfThreads, char *string)
		: server(MAX_NUMBER_OF_CLIENT), numberOfThreads(numberOfThreads), fileName(string){
	std::cout << "server process" << std::endl;
	server.run();
	server.bind(std::bind((&plazza::ProcessHandler::handleNewPackets), this, std::placeholders::_1, std::placeholders::_2));
}

void plazza::ProcessHandler::handleNewPackets(const plazza::network::Packet &packet, size_t idClient) {
	std::cout << "ProcessHandler HandleNewPackets" << std::endl;
	if (packet.isResponse()) {
/*
		 threadOccupancy.at(idClient) = std::stoul(packet.data);
*/
	 }
}

plazza::ProcessHandler::~ProcessHandler() {

}

void plazza::ProcessHandler::feed(const std::vector<plazza::command> &commands) {
	std::cout << "feed" << std::endl;
	for (auto it = commands.begin(); it < commands.end(); it++) {
		if (areProcessesFull()) {
			std::cout << "Spawning a new process" << std::endl;
			spawnANewProcess();
			threadOccupancy.push_back(numberOfThreads);
		}
		std::cout << "dans le for" << std::endl;
		auto lessBusyThread = std::min_element(threadOccupancy.begin(), threadOccupancy.end());
		size_t value = *(std::find(threadOccupancy.begin(), threadOccupancy.end(), (*lessBusyThread)));
		sendTask(*it, lessBusyThread - threadOccupancy.begin());
	}
}

void plazza::ProcessHandler::sendTask(const plazza::command command, long clientNumber) {
	network::Packet packet;
	
	sleep(5);
	std::cout << "Client " << clientNumber << " " << server.getCurrentNumberOfClient() << " size " << server.getClientList().size() << " " << server.getClientList().empty() << std::endl;
	if (server.getClientList().empty() || clientNumber > server.getCurrentNumberOfClient()) {
		std::cout << "return;" << std::endl;
		return;
	}
	std::cout << "send task" << clientNumber << " " << server.getCurrentNumberOfClient() << std::endl;
	packet.data = "data";
	packet.statusCode = network::StatusCode::QUERY;
	server.send(packet, server.getClientList().at((unsigned long)clientNumber));
}

void plazza::ProcessHandler::queryProcessOccupancy() {
	for (auto it = server.getClientList().begin(); it < server.getClientList().end(); it++) {
		server.send(network::Packet::QUERY, *it);
	}
}

void plazza::ProcessHandler::spawnANewProcess() {
	pid_t tmp;
	
	if ((tmp = fork()) == -1)
		throw std::runtime_error("Impossible to fork(), cannot spawn a new process");
	if (tmp == 0) {
		char **tab = new char*[6];
		tab[0] = strdup(fileName);
		tab[1] = strdup(std::to_string(numberOfThreads).c_str());
		tab[2] = strdup("-c");
		tab[3] = strdup("-p");
		tab[4] = strdup(std::to_string(server.getPort()).c_str());
		tab[5] = nullptr;
		std::cout << tab << std::endl;
		execvp(fileName, tab);
	}
	childProcessList.push_back(tmp);
}
bool plazza::ProcessHandler::areProcessesFull() const {
	for (std::size_t i = 0; i < threadOccupancy.size(); ++i) {
		if (threadOccupancy.at(i) != 0)
			return (false);
	}
	return (true);
}
std::vector<size_t> plazza::ProcessHandler::getProcessOccupancy() const {
	return threadOccupancy;
}
