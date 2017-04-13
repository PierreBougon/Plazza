//
// Created by Pierre Bougon on 13/04/17.
//

#ifndef CPP_PLAZZA_XORCIPHER_HPP_
#define CPP_PLAZZA_XORCIPHER_HPP_

#include "ACipher.hpp"

namespace plazza
{
    class XORCipher : public ACipher
    {
    public:
        XORCipher(size_t _keySize);

        virtual ~XORCipher();

    private:
        char cipherChar(char const c, Byte const keyc) const override;
        char unCipherChar(char const c, Byte const keyc) const override;
    };
}


#endif // !CPP_PLAZZA_XORCIPHER_HPP_
