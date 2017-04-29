
//
// Created by Pierre Bougon on 24/04/17.
//

#ifndef CPP_PLAZZA_STATUSCODE_HPP_
#define CPP_PLAZZA_STATUSCODE_HPP_


#include <ostream>

namespace plazza
{
    namespace network
    {
        struct StatusCode
        {
            StatusCode(int _code);
            StatusCode();
            StatusCode(StatusCode const &other);

            int code;


            // Operators
            StatusCode &operator=(const network::StatusCode &other);
            bool operator==(const StatusCode &rhs) const;
            bool operator!=(const StatusCode &rhs) const;
            bool operator<(const StatusCode &rhs) const;
            bool operator>(const StatusCode &rhs) const;
            bool operator<=(const StatusCode &rhs) const;
            bool operator>=(const StatusCode &rhs) const;

            /***************************************************************************************
            * Static basic definitions based on http status code method with our own implementation
            *
            * The main difference is that the client also send an appropriate code to server
            * This is useful to have bidirectional behavior with complete communication on both sides
            ***************************************************************************************/

            // Success
            static const StatusCode OK;
            static const StatusCode CREATED;
            static const StatusCode ACCEPTED;
            static const StatusCode IN_PROGRESS;

            // Client Error
            static const StatusCode BAD_REQUEST;
            static const StatusCode FORBIDDEN;
            static const StatusCode CLIENT_TIME_OUT;
            static const StatusCode NOT_FOUND;

            // Server Error
            static const StatusCode INTERNAL_SERVER_ERROR;
            static const StatusCode GATEWAY_TIMEOUT;
            static const StatusCode NOT_IMPLEMENTED;
    
            //QUERY
            static const StatusCode QUERY;
            // OTHER
            static const StatusCode CORRUPTED;
            static const StatusCode DISCONNECTED;
            static const StatusCode NOTHING;

            
        };
    }
}

std::ostream &operator<<(std::ostream &os, const plazza::network::StatusCode &code);

#endif // !CPP_PLAZZA_STATUSCODE_HPP_
