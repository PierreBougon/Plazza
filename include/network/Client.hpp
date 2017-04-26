//
// Created by Pierre Bougon on 20/04/17.
//

#ifndef CPP_PLAZZA_CLIENT_HPP_
#define CPP_PLAZZA_CLIENT_HPP_


#include <socket/TCPClient.hpp>
#include <thread>
#include <mutex>
#include "tools/Singleton.hpp"

namespace plazza
{
    namespace network
    {
        class Client : public TCPClient, public Singleton<Client>
        {
        private:
            Client(uint16_t port, const std::string &hostname);
            Client(Client const &other) = delete;
            Client &operator=(Client const &other) = delete;

        public:
            // Use getInstance to create / get instance you should NEVER use ctor or errors may occurs
            Client();

            // Use this method as the constructor
            void Init(uint16_t port, std::string const &host);
            virtual ~Client();
        };
    }
}

#endif // !CPP_PLAZZA_CLIENT_HPP_
