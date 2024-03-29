//
// Created by peau_c on 4/21/17.
//

#ifndef CPP_PLAZZA_PROCESS_HPP
#define CPP_PLAZZA_PROCESS_HPP

#include "FileParser.hpp"
#include "ThreadPool.hpp"
#include "IProcess.hpp"
#include "CmdParser.hpp"
#include "network/Client.hpp"

namespace plazza {
	class Process : public IProcess {
	public:
		Process(size_t numberOfThreads);
		~Process();
		
		bool	shouldQuit() const;
		void	handleNewPackets(const plazza::network::Packet &packet);

		bool isTimeout();

	private:
		network::Client			&client;
		ThreadPool				threadPool;
		std::vector<command>	tasks;

		std::chrono::steady_clock::time_point       baseTime;
	};
}

#endif //CPP_PLAZZA_PROCESS_HPP
