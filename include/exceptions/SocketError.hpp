//
// Created by Pierre Bougon on 22/04/17.
//

#ifndef CPP_PLAZZA_SOCKETERROR_HPP_
#define CPP_PLAZZA_SOCKETERROR_HPP_


#include <stdexcept>

namespace plazza
{
    namespace network
    {
        class SocketError : public std::runtime_error
        {
        public:
            SocketError(const std::string &msg);
            SocketError(const char *msg);

            virtual ~SocketError() throw();
        };
    }
}


#endif // !CPP_PLAZZA_SOCKETERROR_HPP_
