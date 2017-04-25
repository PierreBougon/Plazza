//
// Created by Pierre Bougon on 20/04/17.
//

#include <tools/Logger.hpp>
#include <poll.h>
#include <exceptions/ServerError.hpp>
#include "network/Server.hpp"

plazza::network::Server::Server() : TCPServer(), _running(false)
{

}

plazza::network::Server::Server(size_t maxClient) : TCPServer(maxClient), _running(false)
{

}

void plazza::network::Server::run()
{
    if (_running)
    {
        Logger::log(Logger::Warning, "Server is already running");
        return;
    }
    // todo check out thread launching

    _mutex.lock();
    _thread = std::thread(&_core);
}

void plazza::network::Server::_core()
{
    int ret = 0;
    pollfd listEvent[_maxClient] = {0};

    while (_running)
    {
        //refreshEvents();
        ret = poll(listEvent, _maxClient, _timeout);
        switch (ret)
        {
            case -1:
                //error on poll
                Logger::log(Logger::Error, "Error occurred on poll");
                _running = false;
                break;
            case 0:
                //time out
                Logger::log(Logger::Warning, "Time out on server");
                _running = false;
                break;
            default:
                //check for events
                handleEvents(listEvent);
                break;
        }
    }
    _mutex.unlock();
}

void plazza::network::Server::handleEvents(pollfd *listEvent)
{
    network::Packet inputPacket;
    network::Packet outputPacket;

    checkIncomingConnections();
    for (int i = 0; i < _maxClient; ++i)
    {
        if (listEvent[i].revents & POLLIN)
        {
            inputPacket = receive(listEvent[i].fd);
            outputPacket = processPacket(inputPacket);
            send(outputPacket, listEvent[i].fd);
        }
    }

}

void plazza::network::Server::checkIncomingConnections()
{
    while (addClient());
}

plazza::network::Packet plazza::network::Server::processPacket(const plazza::network::Packet &packet)
{
    return plazza::network::Packet();
}

plazza::network::Server::~Server()
{

}



