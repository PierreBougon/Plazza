//
// Created by Pierre Bougon on 20/04/17.
//

#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <algorithm>
#include "exceptions/SocketError.hpp"
#include "socket/TCPServer.hpp"

plazza::network::TCPServer::TCPServer(uint16_t port, size_t maxClient)
        : ASocket(port), _maxClient(maxClient), _currentClient(0)
{
    initServer();
}

plazza::network::TCPServer::TCPServer(size_t maxClient)
        : ASocket(), _maxClient(maxClient), _currentClient(0)
{
    initServer();
}

void plazza::network::TCPServer::initServer()
{
    if (bind(_socket, static_cast<sockaddr *>(&_servAddr), sizeof(_servAddr)) == -1)
        throw network::SocketError("Cannot bind the socket");
    listen(_socket, static_cast<int>(_maxClient));
}

plazza::network::TCPServer::~TCPServer()
{
    for (sock_t sockfd : _clientList)
    {
        close(sockfd);
    }
}

void plazza::network::TCPServer::send(const network::Packet &packet, sock_t socket)
{
    std::string data = packet.serialize();

    if (::send(socket, data.c_str(), data.size(), 0) == -1)
    {
        removeClient(socket);
    }
}

Packet plazza::network::TCPServer::receive(sock_t socket)
{
    bool            completemode = false;
    network::Packet inputPacket;
    std::string     data;
    char            buf[BUFFER_SIZE];
    ssize_t         ret;

    while (true)
    {
        ret = ::recv(socket, buf, BUFFER_SIZE, 0);
        if (ret == -1)
            throw SocketError("Cannot receive");
        else if (ret == 0 && !completemode)
        {
            // Client disconnected
            removeClient(socket);
            break;
        }
        else if (ret == 0)
            break;
        completemode = true;
        data += buf;
    }
    inputPacket.deserialize(data);
    return std::move(inputPacket);
}

bool plazza::network::TCPServer::addClient()
{
    sockaddr_in clientAddr;
    socklen_t   clientSize;
    sock_t      clientSocket;

    if (_maxClient >= _currentClient)
        return false;
    clientSize = sizeof(clientAddr);
    clientSocket = accept(_socket, static_cast<sockaddr *>(&clientAddr), &clientSize);
    if (clientSocket == -1)
        return false;
    _clientList.push_back(clientSocket);
    send(network::Packet::ACCEPTED, clientSocket);
    ++_currentClient;
    return true;
}

bool plazza::network::TCPServer::removeClient(size_t pos)
{
    if (_currentClient == 0 || pos > _currentClient)
        return false;
    --_currentClient;
    close(_clientList[pos]);
    _clientList.erase(_clientList.begin() + pos);
    return true;
}

bool plazza::network::TCPServer::removeClient(plazza::network::sock_t socket)
{
    int pos;

    if ((pos = findClient(socket)) != -1)
        return removeClient(static_cast<size_t>(pos));
    return false;
}

int plazza::network::TCPServer::findClient(plazza::network::sock_t socket) const
{
    std::vector<sock_t >::const_iterator it = std::find(_clientList.begin(), _clientList.end(), socket);

    if (it == _clientList.end())
        return -1;
    return static_cast<int>(it - _clientList.begin());
}
