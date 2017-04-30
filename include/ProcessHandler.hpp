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
		void feed(const std::vector<plazza::command> &commands);
		void sendTask(const command command, long clientNumber);
		void				queryProcessOccupancy();
		
		network::Server server;
		size_t numberOfThreads;
		std::vector<size_t>	getProcessOccupancy() const;

	private:
		std::vector<size_t>	threadOccupancy;
		char 				*fileName;
		std::vector<pid_t>	childProcessList;
		void handleNewPackets(const plazza::network::Packet &, size_t clientNumber);
		size_t getRemainingSize() const;
		size_t getLeastBusyThread() const;
	};
}


#endif //CPP_PLAZZA_PROCESSHANDLER_HPP
