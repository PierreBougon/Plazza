//
// Created by Pierre Bougon on 20/04/17.
//

#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <algorithm>
#include <tools/Logger.hpp>
#include <iostream>
#include "exceptions/SocketError.hpp"
#include "socket/TCPServer.hpp"

plazza::network::TCPServer::TCPServer(uint16_t port, size_t maxClient)
        : ASocket(port, "localhost"), _maxClient(maxClient + 1), _currentClient(0), _needRefresh(true)
{
    initServer();
}

plazza::network::TCPServer::TCPServer(size_t maxClient)
        : ASocket(4242, "localhost"), _maxClient(maxClient + 1), _currentClient(0), _needRefresh(true)
{
    initServer();
}

void plazza::network::TCPServer::initServer()
{
    int opt = 1;

    ::setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (::bind(_socket, (sockaddr *)(&_servAddr), sizeof(_servAddr)) == -1)
        throw network::SocketError("Cannot bind the socket");
    ::listen(_socket, MAX_BACKLOG_CLIENT);
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

    Logger::log(Logger::DEBUG, "Server Sending: " + data);
    if (::send(socket, data.c_str(), data.size(), 0) == -1)
    {
        removeClient(socket);
    }
}

plazza::network::Packet plazza::network::TCPServer::receive(sock_t socket)
{
    network::Packet inputPacket;
    std::string     data;
    char            buf[BUFFER_SIZE];
    ssize_t         ret;

    ret = ::recv(socket, buf, BUFFER_SIZE, 0);
    if (ret == -1)
        throw SocketError("Cannot receive");
    else if (ret == 0)
    {
        // Client disconnected
        removeClient(socket);
        inputPacket.statusCode = StatusCode::DISCONNECTED;
        return std::move(inputPacket);
    }
    data += buf;
    inputPacket.deserialize(data);
    Logger::log(Logger::DEBUG, "Server Receiving: " + inputPacket.serialize());
    return std::move(inputPacket);
}

bool plazza::network::TCPServer::addClient()
{
    sockaddr_in clientAddr;
    socklen_t   clientSize;
    sock_t      clientSocket;

    if (_maxClient - 1 <= _currentClient) {
        std::cout << "Max client reached" << std::endl;
        return false;
    }
    clientSize = sizeof(clientAddr);
    clientSocket = accept(_socket, (sockaddr *)(&clientAddr), &clientSize);
    if (clientSocket == -1) {
        std::cout << "client socket is fucked" << std::endl;
        return false;
    }
    _clientList.push_back(clientSocket);
    ++_currentClient;
    Logger::log(Logger::DEBUG, "New client connected to the server");
    send(network::Packet::ACCEPTED, clientSocket);
    _needRefresh = true;
    return true;
}

bool plazza::network::TCPServer::removeClient(size_t pos)
{
    if (_currentClient == 0 || pos > _currentClient)
        return false;
    --_currentClient;
    ::close(_clientList[pos]);
    _clientList.erase(_clientList.begin() + pos);
    Logger::log(Logger::DEBUG, "Removing client");
    _needRefresh = true;
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

size_t plazza::network::TCPServer::getCurrentNumberOfClient() const
{
    return _currentClient;
}
const std::vector<plazza::network::sock_t> &plazza::network::TCPServer::getClientList() const {
    return _clientList;
}

