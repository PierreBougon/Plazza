//
// Created by peau_c on 4/26/17.
//

#ifndef CPP_PLAZZA_PROCESSHANDLER_HPP
#define CPP_PLAZZA_PROCESSHANDLER_HPP

#include "IProcessHandler.hpp"
#include "CmdParser.hpp"

namespace plazza {
	class ProcessHandler : public IProcessHandler {
	public:
		ProcessHandler(size_t numberOfThreads, char *string);
		~ProcessHandler();
		
		//TODO PRIVATE SERVER
	    bool areProcessesFull() const;
		void spawnANewProcess();
		
		plazza::network::Server server;
		size_t numberOfThreads;
	private:
		char 				*fileName;
		std::vector<pid_t>	childProcessList;
		std::vector<size_t>	getProcessOccupancy() const;
	};
}


#endif //CPP_PLAZZA_PROCESSHANDLER_HPP
