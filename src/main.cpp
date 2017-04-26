#include <iostream>
#include "ThreadPool.hpp"
#include <unistd.h>
#include <cipher/ICipher.hpp>
#include <cipher/XORCipher.hpp>
#include <cipher/CaesarCipher.hpp>
#include <chrono>
#include <FileParser.hpp>
#include <network/Client.hpp>
#include <network/Server.hpp>
#include <CmdParser.hpp>
#include <CmdParser.hpp>
#include <PlazzaError.hpp>
#include <ProcessHandler.hpp>
#include <Process.hpp>

#ifndef UI
int main(int ac, char **av) {
	bool isClient = false;
	std::size_t nbThreads;
	
	std::cout << ac << std::endl;
	if (ac < 2 || std::stoi(av[1]) <= 0) {
		std::cerr << "usage : ./plazza nb_thread_per_process" << std::endl;
		return (1);
	}
	nbThreads = std::stoul(av[1]);
	//Parser correctment
	if (av[2] && strcmp(av[2], "--client")) {
		plazza::Process ChildProcess(nbThreads);
	}
	else {
		plazza::ProcessHandler ProcessHandler(isClient, nbThreads);
	}
	return 0;
}
#endif
