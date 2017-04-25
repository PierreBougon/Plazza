//
// Created by Pierre Bougon on 25/04/17.
//

#ifndef CPP_PLAZZA_CLIENTERROR_HPP_
#define CPP_PLAZZA_CLIENTERROR_HPP_


#include <stdexcept>

namespace plazza
{
    namespace network
    {
        class ClientError : public std::runtime_error
        {
            ClientError(const std::string &msg);
            ClientError(const char *msg);

            virtual ~Client() throw();

        };
    }
}


#endif // !CPP_PLAZZA_CLIENTERROR_HPP_
