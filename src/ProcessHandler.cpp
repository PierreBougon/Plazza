//
// Created by peau_c on 4/26/17.
//

#include <network/Server.hpp>
#include <iostream>
#include "ProcessHandler.hpp"

plazza::ProcessHandler::ProcessHandler(bool isClient, size_t numberOfThreads) : server(MAX_NUMBER_OF_CLIENT){
	plazza::CmdParser parser;
	server.run();
	std::cout << "server" << std::endl;
	for (std::vector<command> commandList; ;) {
		commandList = parser.getCommands();
		
	}
}

plazza::ProcessHandler::~ProcessHandler() {

}
