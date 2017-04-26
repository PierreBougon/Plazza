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

            void            connect();
            void            run();

            template <typename _Callable, typename... _Args>
            void            bind(_Callable &&callable, _Args&&... args)
            {
                _onReceive = std::bind<void>(std::forward<_Callable>(callable), std::forward<_Args>(args)...);
            }

            void send(const network::Packet &packet, sock_t socket) override;
            Packet receive(sock_t socket) override;

        protected:
            bool                                _running;
            std::thread                         _thread;
            std::mutex                          _mutex;
            std::function<void(const Packet &)> _onReceive;

        private:
            void _core();
        };
    }
}


#endif // !CPP_PLAZZA_TCPCLIENT_HPP_
