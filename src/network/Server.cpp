//
// Created by Pierre Bougon on 20/04/17.
//

#include <unistd.h>
#include <poll.h>
#include "tools/Logger.hpp"
#include "exceptions/ServerError.hpp"
#include "network/Server.hpp"

plazza::network::Server::Server() : TCPServer(), _running(false)
{
}

plazza::network::Server::Server(size_t maxClient) : TCPServer(maxClient), _running(false)
{

}

void plazza::network::Server::run()
{
    if (_running || _thread.joinable())
    {
        Logger::log(Logger::Warning, "Server is already running");
        return;
    }
    // todo check out thread launching

    _mutex.lock();
    _thread = std::thread(&Server::_core, this);
}

void plazza::network::Server::_core()
{
    int ret = 0;
    pollfd listEvent[_maxClient];

    while (_running)
    {
        refreshEvents(listEvent);
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
    for (size_t i = 0; i < _maxClient; ++i)
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
    //TODO
    return plazza::network::Packet();
}

void plazza::network::Server::refreshEvents(pollfd *listEvents)
{
    // TODO opti
    for (size_t i = 0; i < _maxClient; ++i)
    {
        if (i < _clientList.size())
            listEvents[i].fd = _clientList[i];
        else
            listEvents[i].fd = -1;
        listEvents[i].events = POLLIN;
    }
}

plazza::network::Server::~Server()
{
    stop();
}

void plazza::network::Server::wait()
{
    _mutex.lock();
    _mutex.unlock();
}

void plazza::network::Server::stop()
{
    if (!_thread.joinable())
        return;
    _running = false;
    _thread.join();
}

