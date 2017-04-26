//
// Created by Pierre Bougon on 20/04/17.
//

#ifndef CPP_PLAZZA_TCPSERVER_HPP_
#define CPP_PLAZZA_TCPSERVER_HPP_


#include <vector>
#include <network/Packet.hpp>
#include "ASocket.hpp"

namespace plazza
{
    namespace network
    {
        class TCPServer : public ASocket
        {
        public:
            TCPServer(uint16_t _port, size_t maxClient = 5);
            TCPServer(const TCPServer &other) = delete;
            TCPServer(size_t maxClient = 5);

            virtual ~TCPServer();

            void send(const network::Packet &packet, sock_t socket) override;
            Packet receive(sock_t socket) override;

            bool addClient();
            bool removeClient(size_t pos);
            bool removeClient(sock_t socket);

            virtual void run() = 0;

        protected:
            size_t                  _maxClient;
            size_t                  _currentClient;
            std::vector<sock_t>     _clientList;

        private:
            void initServer();

            int findClient(sock_t socket) const;
        };
    }
}


#endif // !CPP_PLAZZA_TCPSERVER_HPP_
