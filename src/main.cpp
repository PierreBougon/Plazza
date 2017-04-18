#include <iostream>
#include <cipher/ICipher.hpp>
#include <cipher/XORCipher.hpp>
#include <cipher/CaesarCipher.hpp>
#include <chrono>
#include <Parser.hpp>

int main(int ac, char **av) {
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

    plazza::Parser emailParser = plazza::Parser::Email;
    plazza::Parser phoneParser = plazza::Parser::PhoneNumber;
    plazza::Parser ip = plazza::Parser::IPAddress;

    emailParser.open(av[1]);
    phoneParser.open(av[1]);
    ip.open(av[1]);
    std::vector<std::string> res = emailParser.find();
    for (int i = 0; i < res.size(); ++i) {
        std::cout << " email : " << res[i] << std::endl;
    }

    res.clear();
    std::cout << std::endl;
    res = phoneParser.find();
    for (int i = 0; i < res.size(); ++i) {
        std::cout << " phone : " << res[i] << std::endl;
    }

    res.clear();
    std::cout << std::endl;
    res = ip.find();
    for (int i = 0; i < res.size(); ++i) {
        std::cout << " ip : " << res[i] << std::endl;
    }
    return 0;
}
