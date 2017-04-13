//
// Created by Pierre Bougon on 13/04/17.
//

#include "CaesarCipher.hpp"

plazza::Caesar::Caesar(size_t _keySize) : ACipher(_keySize)
{}

char plazza::Caesar::cipherChar(char const c, const plazza::Byte keyc) const
{
    return c + keyc;
}

char plazza::Caesar::unCipherChar(char const c, const plazza::Byte keyc) const
{
    return c - keyc;
}

plazza::Caesar::~Caesar()
{
}
