//
// Created by Pierre Bougon on 23/04/17.
//

#include "network/Packet.hpp"

namespace plazza
{
    namespace network
    {
        const Packet OK = Packet(StatusCode::OK);
        const Packet BAD_REQUEST = Packet(StatusCode::BAD_REQUEST);
        const Packet INTERNAL_SERVER_ERROR = Packet(StatusCode::INTERNAL_SERVER_ERROR);
        const Packet ACCEPTED = Packet(StatusCode::ACCEPTED);
        const Packet FORBIDDEN = Packet(StatusCode::FORBIDDEN);
    }
}

plazza::network::Packet::Packet()
        : header(), statusCode(network::StatusCode::OK), data("")
{
}

plazza::network::Packet::Packet(const plazza::network::StatusCode &statusCode, std::string _data)
        :statusCode(statusCode), data(_data)
{
}

plazza::network::Packet::Packet(const plazza::network::Packet &other)
        : header(other.header), statusCode(other.statusCode), data(other.data)
{

}

plazza::network::Packet &plazza::network::Packet::operator=(const plazza::network::Packet &other)
{
    header = other.header;
    statusCode = other.statusCode;
    data = other.data;
    return *this;
}

std::string plazza::network::Packet::serialize() const
{
    std::string serialized;

    serialized += "header=";
    serialized += header.MAGIC_NUMBER;
    serialized += ";";
    // TODO
    return std::move(serialized);
}

bool plazza::network::Packet::deserialize(std::string const &serialized) const
{
    //TODO
    return false;
}


