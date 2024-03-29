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
#include <PlazzaError.hpp>
#include <ProcessHandler.hpp>
#include <Process.hpp>
#include <tools/Logger.hpp>
#include <getopt.h>

static const struct option long_options[] = {
		{"client", 0, 0, 'c'},
		{"server", 0, 0, 's'},
		{"port",   0, 0, 'p'},
		{0,        0, 0, 0}
};

int main(int ac, char **av) {
	
	bool isClient = false;
	std::size_t nbThreads;
	std::string server;
	int port = 0;
	int option;
	
	try {
		if (ac < 2 || std::stoi(av[1]) <= 0) {
			std::cerr << "usage : ./plazza nb_thread_per_process" << std::endl;
			return (1);
		}
		nbThreads = std::stoul(av[1]);
		if (ac > 2) {
			while ((option = getopt_long(ac, av, "cs:p:", long_options, NULL)) != -1)
				switch (option) {
					case 'c':
						isClient = true;
						break;
					case 's':
						server = optarg;
						break;
					case 'p':
						port = std::stoi(optarg);
                        (void)port;
						break;
					case '?':
						break;
					default:
						abort();
				}
		}
		if (isClient) {
			plazza::Process ChildProcess(nbThreads);
			while (!ChildProcess.shouldQuit())
            {
                if (ChildProcess.isTimeout()) {
					break;
				}
            }
		} else {
			Logger::getInstance().setFile("logFile.txt");
			plazza::ProcessHandler processHandler(nbThreads, av[0]);
			plazza::CmdParser cmdParser;
            std::string buffer;

            while (getline(std::cin, buffer)) {
                cmdParser.reset();
                cmdParser.feed(buffer);
                processHandler.queryProcessOccupancy();
                std::vector<plazza::command> cmds = cmdParser.getCommands();
                processHandler.feed(cmds);
            }
            Logger::getInstance().closeFile();
            processHandler.server.stop();
		}
	} catch (std::exception const &err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}
