//
// Created by Pierre Bougon on 20/04/17.
//

#ifndef CPP_PLAZZA_SERVER_HPP_
#define CPP_PLAZZA_SERVER_HPP_


#include <thread>
#include <mutex>
#include <poll.h>
#include "socket/TCPServer.hpp"

namespace plazza
{
    namespace network
    {
        class Server : public TCPServer
        {
        public:
            Server();
            Server(size_t maxClient);

            virtual ~Server();

            void run() override;

        private:
            bool            _running;
            std::thread     _thread;
            std::mutex      _mutex;


        private:
            void _core();
            void handleEvents(pollfd *listEvent);
            void checkIncomingConnections();
            Packet processPacket(Packet const &packet);


            // Static member data
            /// Timeout is set to 2 minutes
            static constexpr size_t          _timeout = 2 * 60 * 10000;
        };
    }
}


#endif // !CPP_PLAZZA_SERVER_HPP_
