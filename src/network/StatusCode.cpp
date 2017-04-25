//
// Created by Pierre Bougon on 24/04/17.
//

#include "network/StatusCode.hpp"
namespace plazza
{
    namespace network
    {
        // Success
        const StatusCode OK                      = StatusCode(200);
        const StatusCode CREATED                 = StatusCode(201);
        const StatusCode ACCEPTED                = StatusCode(202);
        const StatusCode IN_PROGRESS             = StatusCode(209);

        // Client Error
        const StatusCode BAD_REQUEST             = StatusCode(400);
        const StatusCode FORBIDDEN               = StatusCode(401);
        const StatusCode CLIENT_TIME_OUT         = StatusCode(402);
        const StatusCode NOT_FOUND               = StatusCode(402);

        // Server Error
        const StatusCode INTERNAL_SERVER_ERROR   = StatusCode(500);
        const StatusCode GATEWAY_TIMEOUT         = StatusCode(501);
        const StatusCode NOT_IMPLEMENTED         = StatusCode(502);

    }
}


plazza::network::StatusCode::StatusCode(int _code) : code(_code)
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

plazza::network::StatusCode &plazza::network::StatusCode::operator=(const plazza::network::StatusCode &statusCode)
{
    code = statusCode.code;
    return *this;
}

