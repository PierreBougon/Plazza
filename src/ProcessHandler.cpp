//
// Created by peau_c on 4/26/17.
//

#include <network/Server.hpp>
#include <iostream>
#include "ProcessHandler.hpp"

plazza::ProcessHandler::ProcessHandler(bool isClient, int numberOfThreads) {
	network::Server server(MAX_NUMBER_OF_CLIENT);
	server.run();
	std::cout << "server" << std::endl;
}

plazza::ProcessHandler::~ProcessHandler() {

}
