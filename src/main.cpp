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
	
	std::cout << ac << std::endl;
	if (ac < 2 || std::stoi(av[1]) <= 0) {
		std::cerr << "usage : ./plazza nb_thread_per_process" << std::endl;
		return (1);
	}
	if (av[2] && av[2] == "--client")
		isClient = true;
	if (!isClient)
		plazza::ProcessHandler(isClient, std::stoi(av[1]));
	else
	//	plazza::Process();
	/*
    plazza::ThreadPool *toto;
    toto = new plazza::ThreadPool(atoi(av[1]));
    getchar();
    delete toto;*/
/*
    std::cout << "Hello, World!" << std::endl;
	while (1) {
		//read sur l'entree standard et dispatch les orders
	}
*/
/*    std::srand(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    plazza::ICipher const &cipher = plazza::XORCipher(2);
    std::string str = "Je suis une string !";

    std::cout << "1 : " << str << std::endl;
    str += cipher;
    std::cout << "2 : " << str << std::endl;
    str -= cipher;
    std::cout << "3 : " << str << std::endl;*/

       /*plazza::FileParser parser;

       parser.open(av[1]);
       std::vector<std::string> res = parser.getEmails();
       for (int i = 0; i < res.size(); ++i) {
           std::cout << " email : " << res[i] << std::endl;
       }

       res.clear();
       std::cout << std::endl;
       res = parser.getPhones();
       for (int i = 0; i < res.size(); ++i) {
           std::cout << " phone : " << res[i] << std::endl;
       }

       res.clear();
       std::cout << std::endl;
       res = parser.getIps();
       for (int i = 0; i < res.size(); ++i) {
           std::cout << " ip : " << res[i] << std::endl;
       }
*/
    return 0;
}
#endif
