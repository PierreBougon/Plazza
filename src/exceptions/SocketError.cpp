//
// Created by Pierre Bougon on 22/04/17.
//

#include <netinet/in.h>
#include "exceptions/SocketError.hpp"

plazza::network::SocketError::SocketError(const std::string &msg) : runtime_error(msg)
{}

plazza::network::SocketError::SocketError(const char *msg) : runtime_error(msg)
{
}

plazza::network::SocketError::~SocketError() throw()
{
}
