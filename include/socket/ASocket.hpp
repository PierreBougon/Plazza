//
// Created by Pierre Bougon on 20/04/17.
//

#ifndef CPP_PLAZZA_ASOCKET_HPP_
#define CPP_PLAZZA_ASOCKET_HPP_


#include <netinet/in.h>
#include <string>
#include <netdb.h>
#include <network/Packet.hpp>

namespace plazza
{
    namespace network
    {
        typedef int sock_t;

        class ASocket
        {
        public:
            ASocket(uint16_t _port = 4242, const std::string &_hostname = "localhost");
            ASocket(const ASocket &other) = delete;
            ASocket() = delete;

            virtual ~ASocket();

            sock_t              getSocket() const;
            uint16_t            getPort() const;
            const std::string   &getHostname() const;

            virtual void send(const network::Packet &packet, sock_t socket) = 0;
            virtual Packet receive(sock_t socket) = 0;

        public:
            static constexpr size_t BUFFER_SIZE = 1024;

        protected:
            sock_t          _socket;
            uint16_t        _port;
            std::string     _hostname;
            sockaddr_in     _servAddr;
            hostent         *_server;

        private:
            void init();
        };
    }
}


#endif // !CPP_PLAZZA_ASOCKET_HPP_
