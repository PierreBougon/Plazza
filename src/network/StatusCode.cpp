//
// Created by Pierre Bougon on 24/04/17.
//

#include <tools/Logger.hpp>
#include <iostream>
#include "network/StatusCode.hpp"
namespace plazza
{
    namespace network
    {
        // Success
        const StatusCode StatusCode::OK                     = StatusCode(200);
        const StatusCode StatusCode::CREATED                = StatusCode(201);
        const StatusCode StatusCode::ACCEPTED               = StatusCode(202);
        const StatusCode StatusCode::IN_PROGRESS            = StatusCode(209);

        // Client Error
        const StatusCode StatusCode::BAD_REQUEST            = StatusCode(400);
        const StatusCode StatusCode::FORBIDDEN              = StatusCode(401);
        const StatusCode StatusCode::CLIENT_TIME_OUT        = StatusCode(402);
        const StatusCode StatusCode::NOT_FOUND              = StatusCode(402);

        // Server Error
        const StatusCode StatusCode::INTERNAL_SERVER_ERROR  = StatusCode(500);
        const StatusCode StatusCode::GATEWAY_TIMEOUT        = StatusCode(501);
        const StatusCode StatusCode::NOT_IMPLEMENTED        = StatusCode(502);

        // OTHER
        const StatusCode StatusCode::CORRUPTED              = StatusCode(700);
        const StatusCode StatusCode::DISCONNECTED           = StatusCode(701);
        const StatusCode StatusCode::NOTHING                = StatusCode(702);


    }
}


plazza::network::StatusCode::StatusCode(int _code) : code(_code)
{
}

plazza::network::StatusCode::StatusCode() : code(200)
{
}

plazza::network::StatusCode::StatusCode(const plazza::network::StatusCode &other) : code(other.code)
{
}


std::ostream &operator<<(std::ostream &os, const plazza::network::StatusCode &statusCode)
{
    os << "code: " << statusCode.code;
    return os;
}

plazza::network::StatusCode &plazza::network::StatusCode::operator=(const plazza::network::StatusCode &other)
{
    code = other.code;
    return *this;
}

bool plazza::network::StatusCode::operator==(const plazza::network::StatusCode &rhs) const
{
    return code == rhs.code;
}

bool plazza::network::StatusCode::operator!=(const plazza::network::StatusCode &rhs) const
{
    return rhs.code != this->code;
}

bool plazza::network::StatusCode::operator<(const plazza::network::StatusCode &rhs) const
{
    return code < rhs.code;
}

bool plazza::network::StatusCode::operator>(const plazza::network::StatusCode &rhs) const
{
    return code > rhs.code;
}

bool plazza::network::StatusCode::operator<=(const plazza::network::StatusCode &rhs) const
{
    return code <= rhs.code;
}

bool plazza::network::StatusCode::operator>=(const plazza::network::StatusCode &rhs) const
{
    return code >= rhs.code;
}

