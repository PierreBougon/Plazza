//
// Created by Pierre Bougon on 13/04/17.
//

#include <iostream>
#include "cipher/XORCipher.hpp"

plazza::XORCipher::XORCipher(size_t _keySize) : ACipher(_keySize)
{
}

char plazza::XORCipher::cipherChar(char const c, const plazza::Byte keyc) const
{
    return c ^ keyc;
}

char plazza::XORCipher::unCipherChar(char const c, const plazza::Byte keyc) const
{
    return c ^ keyc;
}

plazza::XORCipher::~XORCipher()
{

}
