//
// Created by Pierre Bougon on 20/04/17.
//

#ifndef CPP_PLAZZA_TCPCLIENT_HPP_
#define CPP_PLAZZA_TCPCLIENT_HPP_


#include <mutex>
#include <thread>
#include "ASocket.hpp"

namespace plazza
{
    namespace network
    {
        class TCPClient : public ASocket
        {
        public:
            TCPClient(uint16_t port, const std::string &hostname);
            virtual ~TCPClient();

            virtual void    connect();
            void            run();

            void send(const network::Packet &packet, sock_t socket) const override;
            Packet receive(sock_t socket) override;




            /// Called when something is received from server
            virtual void onReceive(const network::Packet &packet) = 0;

        protected:
            bool                   _running;
            std::thread            _thread;
            std::mutex             _mutex;


        private:
            void _core();
        };
    }
}


#endif // !CPP_PLAZZA_TCPCLIENT_HPP_
