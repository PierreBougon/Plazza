//
// Created by Pierre Bougon on 20/04/17.
//

#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
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

void plazza::network::TCPServer::send(const network::Packet &packet, sock_t socket) const
{
    if (::send(socket, &packet, Packet::size, 0) == -1)
    {
        // TODO close connection with client
    }
}

Packet plazza::network::TCPServer::receive(sock_t socket)
{
    // TODO receive the whole network packet of the client
    ASocket::receive(0);
    return Packet();
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
