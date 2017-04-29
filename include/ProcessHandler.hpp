//
// Created by peau_c on 4/26/17.
//

#ifndef CPP_PLAZZA_PROCESSHANDLER_HPP
#define CPP_PLAZZA_PROCESSHANDLER_HPP

#include "IProcessHandler.hpp"
#include "CmdParser.hpp"
#include "network/Server.hpp"

namespace plazza {
	class ProcessHandler : public IProcessHandler {
	public:
		ProcessHandler(size_t numberOfThreads, char *string);
		~ProcessHandler();
		
		//TODO PRIVATE SERVER
	    bool areProcessesFull() const;
		void spawnANewProcess();
		
		network::Server server;
		size_t numberOfThreads;
		std::vector<size_t>	getProcessOccupancy() const;

	private:
		char 				*fileName;
		std::vector<pid_t>	childProcessList;
	};
}


#endif //CPP_PLAZZA_PROCESSHANDLER_HPP
