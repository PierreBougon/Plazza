//
// Created by Pierre Bougon on 13/04/17.
//

#include "ACipher.hpp"

namespace plazza
{
    ACipher::ACipher(size_t keySize) : _keySize(keySize)
    {
        _key.reserve(_keySize);
        for (Byte &c : _key)
        {
            c[0] = std::rand() % 1;
        }
    }

    void ACipher::generateKey()
    {
        for (Byte &c : _key)
        {
            c[0] = std::rand() % 1;
        }
    }

    Byte const &ACipher::operator[](size_t n) const
    {
        return _key[n];
    }

    std::string const &operator+=(std::string const &toCipher, ACipher const &key)
    {
        return key.cipher(toCipher);
    }

    std::string const &operator+(std::string const &toCipher, ACipher const &key)
    {
        return key.cipher(toCipher);
    }

    std::string const &operator-=(std::string const &toUnCipher, ACipher const &key)
    {
        return key.unCipher(toUnCipher);
    }

    std::string const &operator-(std::string const &toUnCipher, ACipher const &key)
    {
        return key.unCipher(toUnCipher);
    }
}