//
// Created by Pierre Bougon on 20/04/17.
//

#include <unistd.h>
#include <poll.h>
#include <iostream>
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
        Logger::log(Logger::WARNING, "Server is already running");
        return;
    }
    // todo check out thread launching

    _running = true;
    _mutex.lock();
    _thread = std::thread(&Server::_core, this);
}

void plazza::network::Server::_core()
{
    int ret = 0;
    pollfd listEvent[_maxClient];

    Logger::log(Logger::DEBUG, "Launching core server");
    while (_running)
    {
        refreshEvents(listEvent);
        ret = poll(listEvent, _maxClient, _timeout);
        //Logger::log(Logger::DEBUG, "poll() catched something" + std::to_string(ret));
        switch (ret)
        {
            case -1:
                //error on poll

                Logger::log(Logger::ERROR, "Error occurred on poll");
                _running = false;
                break;
            case 0:
                // TODO what is timeouted
                //time out
                Logger::log(Logger::WARNING, "Time out on server");
                _running = false;
                break;
            default:
                //check for events
                handleEvents(listEvent);
                break;
        }
        Logger::log(Logger::DEBUG, "core loop");

    }
    Logger::log(Logger::DEBUG, "sortie du core, _running = false");
    _mutex.unlock();
    Logger::log(Logger::DEBUG, "sortie du core, apres le unlock");
}

void plazza::network::Server::handleEvents(pollfd *listEvent)
{
    network::Packet inputPacket;
    network::Packet outputPacket;

    for (size_t i = 0; i < _currentClient + 1; ++i)
    {
        if (listEvent[i].revents == 0)
            continue;

        if (listEvent[i].revents != POLLIN)
        {
            // Error not requested event
            _running = false;
            break;
        }

        if (listEvent[i].fd == _socket)
        {
            checkIncomingConnections();
        }
        else
        {
            inputPacket = receive(listEvent[i].fd);
            outputPacket = processPacket(inputPacket);
            if (outputPacket.isResponse())
                send(outputPacket, listEvent[i].fd);
            else
                _onReceive(inputPacket, i - 1);
        }
    }

}

void plazza::network::Server::checkIncomingConnections()
{
	std::cout << "New server client" << std::endl;
    // TODO multiple client addition ?
    addClient();
}

/**
 * Basic packet processing from server which will handle
 * basic responses as corrupted packets and no query requests
 */
plazza::network::Packet plazza::network::Server::processPacket(const plazza::network::Packet &packet)
{
    plazza::network::Packet outputPacket;
    std::cout << "new packet on server" << std::endl;
    if (!packet.isQuery() && !packet.isSpecific())
    {
        // Actually we don't do anything
        outputPacket = Packet::NOTHING;
        return std::move(outputPacket);
    }
    outputPacket = Packet::NOTHING;
    return std::move(outputPacket);
}

void plazza::network::Server::refreshEvents(pollfd *listEvents)
{
    size_t i = 1;

    // TODO opti
    if (!_needRefresh)
        return;
    listEvents[0].fd = _socket;
    listEvents[0].events = POLLIN;
    for (size_t clientPos = 0; clientPos < _maxClient; ++clientPos)
    {
        if (clientPos < _currentClient)
        {
            listEvents[i].fd = _clientList[clientPos];
        }
        else
        {
            listEvents[i].fd = -1;
        }
        listEvents[i].events = POLLIN;
        ++i;
    }
    _needRefresh = false;
}

plazza::network::Server::~Server()
{
}

void plazza::network::Server::wait()
{
    while (_running)
        std::this_thread::sleep_for(std::chrono::milliseconds(100000));
}

void plazza::network::Server::stop()
{
    if (!_thread.joinable())
        return;
    _running = false;
    ::shutdown(_socket, SHUT_RD);
    _thread.join();
}

