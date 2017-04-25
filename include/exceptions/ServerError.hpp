//
// Created by Pierre Bougon on 25/04/17.
//

#ifndef CPP_PLAZZA_SERVERERROR_HPP_
#define CPP_PLAZZA_SERVERERROR_HPP_

#include <exception>
#include <string>
#include <stdexcept>

namespace plazza
{
    namespace network
    {
        class ServerError : public std::runtime_error
        {
            ServerError(const std::string &msg);
            ServerError(const char *msg);

            virtual ~ServerError()() throw();
        };
    }
}


#endif // !CPP_PLAZZA_SERVERERROR_HPP_
