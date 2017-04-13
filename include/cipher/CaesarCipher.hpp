//
// Created by Pierre Bougon on 13/04/17.
//

#ifndef CPP_PLAZZA_CAESER_HPP_
#define CPP_PLAZZA_CAESER_HPP_


#include "ACipher.hpp"

namespace plazza
{
    class Caesar : public ACipher
    {
    public:
        Caesar(size_t _keySize);

        virtual ~Caesar();

    public:
        char cipherChar(char const c, Byte const keyc) const override;

        char unCipherChar(char const c, Byte const keyc) const override;
    };
}


#endif // !CPP_PLAZZA_CAESER_HPP_
