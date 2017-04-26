//
// Created by Pierre Bougon on 20/04/17.
//

#include <tools/Logger.hpp>
#include "network/Client.hpp"

plazza::network::Client::Client(uint16_t port, const std::string &hostname) : TCPClient(port, hostname)
{}

plazza::network::Client::Client() : TCPClient(0, "")
{
}

void plazza::network::Client::Init(uint16_t port, std::string const &host)
{
    _port = port;
    _hostname = host;
}

plazza::network::Client::~Client()
{
}
