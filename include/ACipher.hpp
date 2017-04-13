//
// Created by Pierre Bougon on 13/04/17.
//

#ifndef CPP_PLAZZA_CIPHER_HPP_
#define CPP_PLAZZA_CIPHER_HPP_

#include <string>
#include <vector>
#include <bitset>

namespace plazza
{
    typedef std::bitset<8>              Byte;

    class ACipher
    {
    public:
        // Constructors
        ACipher() = delete;
        ACipher(const ACipher &copy) = delete;
        ACipher(size_t _keySize);

        /// Change the base key of your cipher
        virtual void generateKey();

        virtual std::string const &cipher(std::string const &tocipher) const = 0;
        virtual std::string const &unCipher(std::string const &touncipher) const = 0;

    protected:
        Byte const &operator[](size_t n) const;

    private:
        /// Size of the key in byte
        size_t                  _keySize;
        /// The key stores randomly _keySize std::bitset<8> which is the definition of a byte
        std::vector<Byte>       _key;
    };

    // Cipher operators
    std::string const &operator+=(std::string const &toCipher, ACipher const &key);
    std::string const &operator+(std::string const &toCipher, ACipher const &key);

    // UnCipher operators
    std::string const &operator-=(std::string const &toUnCipher, ACipher const &key);
    std::string const &operator-(std::string const &toUnCipher, ACipher const &key);
}

#endif // !CPP_PLAZZA_CIPHER_HPP_
