//
// Created by Pierre Bougon on 13/04/17.
//

#ifndef CPP_PLAZZA_ICIPHER_HPP_
#define CPP_PLAZZA_ICIPHER_HPP_

#include <string>


namespace plazza
{
    class ACipher;
    typedef unsigned char              Byte;

    class ICipher
    {
    public:
        virtual ~ICipher();

        virtual void generateKey() = 0;

        virtual char cipherChar(char const c, Byte const keyc) const = 0;
        virtual char unCipherChar(char const c, Byte const keyc) const = 0;

        virtual std::string cipher(std::string const &tocipher) const = 0;
        virtual std::string unCipher(std::string const &touncipher) const = 0;
    };

    // cipher operators
    std::string operator+=(std::string &toCipher, ICipher const &key);
    std::string operator+(std::string const &toCipher, ICipher const &key);

    // UnCipher operators
    std::string operator-=(std::string &toUnCipher, ICipher const &key);
    std::string operator-(std::string const &toUnCipher, ICipher const &key);
}

#endif // !CPP_PLAZZA_ICIPHER_HPP_
