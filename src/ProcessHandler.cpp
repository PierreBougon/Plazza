//
// Created by peau_c on 4/26/17.
//

#include <network/Server.hpp>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include "ProcessHandler.hpp"


plazza::ProcessHandler::ProcessHandler(bool isClient, size_t numberOfThreads, char *string)
		: server(MAX_NUMBER_OF_CLIENT), numberOfThreads(numberOfThreads), fileName(string){
	server.run();
	std::cout << "server" << std::endl;
}

plazza::ProcessHandler::~ProcessHandler() {

}

std::vector<size_t> plazza::ProcessHandler::getProcessOccupancy() const {
	std::vector<size_t> ret;
	
	for (size_t i = 0; i < server.getCurrentNumberOfClient(); i++) {
		ret.push_back(1);
		//Call tout les process et leur demander si ils ont du boulot
	}
	return ret;
}

bool plazza::ProcessHandler::areProcessesFull() const {
	std::vector<size_t> processesThreadOccupancy = getProcessOccupancy();
	for (size_t i = 0; i < processesThreadOccupancy.size(); i++) {
		if (processesThreadOccupancy.at(i) < numberOfThreads)
			return false;
	}
	return true;
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
