#include <iostream>
#include <cipher/ICipher.hpp>
#include <cipher/XORCipher.hpp>
#include <cipher/CaesarCipher.hpp>
#include <chrono>

int main() {
/*
    std::cout << "Hello, World!" << std::endl;
	while (1) {
		//read sur l'entree standard et dispatch les orders
	}
*/
    std::srand(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    plazza::ICipher const &cipher = plazza::XORCipher(2);
    std::string str = "Je suis une string !";

    std::cout << "1 : " << str << std::endl;
    str += cipher;
    std::cout << "2 : " << str << std::endl;
    str -= cipher;
    std::cout << "3 : " << str << std::endl;
    return 0;
}
