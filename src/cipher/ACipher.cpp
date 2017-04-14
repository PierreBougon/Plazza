//
// Created by Pierre Bougon on 13/04/17.
//

#include <iostream>
#include "cipher/ACipher.hpp"

namespace plazza
{
    ACipher::ACipher(size_t keySize) : _keySize(keySize)
    {
        _key.reserve(_keySize);
        generateKey();
    }

    void ACipher::generateKey()
    {
        for (size_t i = 0; i < _keySize; ++i)
        {
            _key.push_back(static_cast<Byte>(std::rand() % 256));
        }
    }

    std::string plazza::ACipher::cipher(std::string const &tocipher) const
    {
        std::string ciphered;

        ciphered.reserve(tocipher.size());
        for (size_t i = 0; i < tocipher.size(); ++i)
        {
            ciphered.push_back(tocipher[i]);
            for (size_t j = 0; j < _key.size(); ++j)
            {
                ciphered[i] = this->cipherChar(ciphered[i], _key[j]);
            }
        }
        return std::move(ciphered);
    }

    std::string plazza::ACipher::unCipher(std::string const &touncipher) const
    {
        std::string unciphered;

        unciphered.reserve(touncipher.size());
        for (size_t i = 0; i < touncipher.size(); ++i)
        {
            unciphered.push_back(touncipher[i]);
            for (int j = static_cast<int>(_keySize - 1); j >= 0; --j)
            {
                unciphered[i] = this->unCipherChar(unciphered[i], _key[j]);
            }
        }
        return std::move(unciphered);
    }

    Byte const &ACipher::operator[](size_t n) const
    {
        return _key[n];
    }

    ACipher::~ACipher()
    {

    }
}
