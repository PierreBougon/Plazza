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
    if (av[2] && strcmp(av[2], "--client") == 0) {
        plazza::Process ChildProcess(nbThreads);
    } else {
        std::cout << "Nous somme actuellement dans le else mon cher Pierre !" << std::endl;
        plazza::ProcessHandler ProcessHandler(isClient, nbThreads);
        plazza::CmdParser cmdParser;

//		std::vector<plazza::command> commands = cmdParser.getCommands();
        while (1);
        /*ProcessHandler.server.wait();
        for (size_t i = 0; i < commands.size(); ++i) {
            std::cout << i << std::endl;
            std::cout << "avant le send" << std::endl;
            sleep(10);
            //ProcessHandler.server.send(plazza::network::Packet::OK, ProcessHandler.server);
            std::cout << "apres le send" << std::endl;
        }*/
    }
    return 0;
}

#endif
