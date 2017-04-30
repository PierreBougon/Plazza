//
// Created by sauvau_m on 4/18/17.
//

#include <PlazzaUI.hpp>
#include <iostream>
#include <getopt.h>
#include <Process.hpp>

static const struct option long_options[] = {
        {"client", 0, 0, 'c'},
        {"server", 0, 0, 's'},
        {"port",   0, 0, 'p'},
        {0,        0, 0, 0}
};

int main(int ac, char **av)
{
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
                        break;
                    case '?':
                        break;
                    default:
                        abort();
                }
        }
        if (isClient) {
            plazza::Process ChildProcess(nbThreads);
        } else {
            plazza::PlazzaUI ui(ac, av);
            ui.getApp().exec();
            ui.processHandler.server.stop();
            return 0;
        }
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    };
    return 0;
}
