//
// Created by Pierre Bougon on 13/04/17.
//

#ifndef CPP_PLAZZA_CIPHER_HPP_
#define CPP_PLAZZA_CIPHER_HPP_

#include <string>
#include <vector>
#include <bitset>
#include "ICipher.hpp"

namespace plazza
{
    /**
     * \class ACipher
     * \brief basic implementation to create your own cipher
     */
    class ACipher : public ICipher
    {
    public:
        // Constructors
        ACipher() = delete;
        ACipher(const ACipher &copy) = delete;
        ACipher(size_t _keySize);

        virtual ~ACipher();

        /// Change the base key of your cipher
        virtual void generateKey();

        std::string cipher(std::string const &tocipher) const override;

        std::string unCipher(std::string const &touncipher) const override;

    protected:
        Byte const &operator[](size_t n) const;

    protected:
        /// Size of the key in byte
        size_t                  _keySize;
        /// The key stores randomly _keySize bytes
        std::vector<Byte>       _key;
    };
}

#endif // !CPP_PLAZZA_CIPHER_HPP_
