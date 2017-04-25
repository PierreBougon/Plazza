//
// Created by Pierre Bougon on 25/04/17.
//

#include "exceptions/ServerError.hpp"

plazza::network::ServerError::ServerError(const std::string &msg) : runtime_error(msg)
{
}

plazza::network::ServerError::ServerError(const char *msg) : runtime_error(msg)
{

}

plazza::network::ServerError::~ServerError()
{
}
