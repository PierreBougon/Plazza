//
// Created by Pierre Bougon on 13/04/17.
//

#include <iostream>
#include "cipher/ICipher.hpp"

namespace plazza
{
    std::string operator+=(std::string &toCipher, ICipher const &key)
    {
        return (toCipher = key.cipher(toCipher));
    }

    std::string operator+(std::string const &toCipher, ICipher const &key)
    {
        return (std::move(key.cipher(toCipher)));
    }

    std::string operator-=(std::string &toUnCipher, ICipher const &key)
    {
        return (toUnCipher = key.unCipher(toUnCipher));
    }

    std::string operator-(std::string const &toUnCipher, ICipher const &key)
    {
        return (std::move(key.unCipher(toUnCipher)));
    }

    ICipher::~ICipher()
    {

    }
}
