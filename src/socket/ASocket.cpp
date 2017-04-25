//
// Created by Pierre Bougon on 20/04/17.
//

#include <unistd.h>
#include <cstring>
#include <exceptions/SocketError.hpp>
#include "socket/ASocket.hpp"

plazza::network::ASocket::ASocket(uint16_t _port, const std::string &_hostname)
        : _socket(-1), _port(_port), _hostname(_hostname), _servAddr()
{
    std::memset((char *)&_servAddr, 0, sizeof(_servAddr));
    init();
}

void plazza::network::ASocket::init()
{
    _socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0)
        throw network::SocketError("Cannot create socket");
    _servAddr.sin_family = AF_INET;
    _servAddr.sin_port = htons(_port);
    _servAddr.sin_addr.s_addr = INADDR_ANY;
}

plazza::network::sock_t plazza::network::ASocket::getSocket() const
{
    return _socket;
}

uint16_t plazza::network::ASocket::getPort() const
{
    return _port;
}

const std::string &plazza::network::ASocket::getHostname() const
{
    return _hostname;
}

plazza::network::ASocket::~ASocket()
{
    if (_socket >= 0)
        close(_socket);
}

