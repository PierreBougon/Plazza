//
// Created by Pierre Bougon on 23/04/17.
//

#include <PlazzaError.hpp>
#include "network/Packet.hpp"

namespace plazza
{
    namespace network
    {
        const Packet OK(StatusCode::OK);
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
    serialized += "status_code=";
    serialized += statusCode.code;
    serialized += ";";
    serialized += "data=";
    serialized += data;
    serialized += ";";
    return std::move(serialized);
}

bool plazza::network::Packet::deserialize(std::string const &serialized)
{
    std::string copy = serialized;

    std::string first = copy.substr(0, copy.find(";"));
    std::string second = first.substr(copy.find("="), first.size());
    copy.erase(0, copy.find(";") + 1);

    if (header.MAGIC_NUMBER != std::stoi(second))
        return (false);
    first = copy.substr(0, copy.find(";"));
    second = first.substr(copy.find("="), first.size());
    copy.erase(0, copy.find(";") + 1);
    statusCode.code = std::stoi(second);
    first = copy.substr(0, copy.find(";"));
    second = first.substr(copy.find("="), first.size());
    copy.erase(0, copy.find(";") + 1);
    data = second;
    return (true);
}


