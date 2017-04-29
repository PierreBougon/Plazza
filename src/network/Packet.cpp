//
// Created by Pierre Bougon on 23/04/17.
//

#include <PlazzaError.hpp>
#include <iostream>
#include <tools/Logger.hpp>
#include "network/Packet.hpp"

namespace plazza
{
    namespace network
    {
        const Packet Packet::OK                     = Packet(StatusCode::OK);
        const Packet Packet::BAD_REQUEST            = Packet(StatusCode::BAD_REQUEST);
        const Packet Packet::INTERNAL_SERVER_ERROR  = Packet(StatusCode::INTERNAL_SERVER_ERROR);
        const Packet Packet::ACCEPTED               = Packet(StatusCode::ACCEPTED);
        const Packet Packet::FORBIDDEN              = Packet(StatusCode::FORBIDDEN);
        const Packet Packet::QUERY                  = Packet(StatusCode::QUERY);
        const Packet Packet::NOTHING                = Packet(StatusCode::NOTHING);
    }
}

plazza::network::Packet::Packet()
        : header(), statusCode(network::StatusCode::OK), data("")
{
}

plazza::network::Packet::Packet(const plazza::network::StatusCode &_statusCode, std::string _data)
        : header(), statusCode(_statusCode), data(_data)
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
    serialized += std::to_string(header.MAGIC_NUMBER);
    serialized += ";";
    serialized += "status_code=";
    serialized += std::to_string(statusCode.code);
    serialized += ";";
    serialized += "data=";
    serialized += data;
    serialized += ";";
    return std::move(serialized);
}

bool plazza::network::Packet::deserialize(std::string const &serialized)
{
    try
    {
        std::string copy = serialized;

        std::string first = copy.substr(0, copy.find(";"));
        std::string second = first.substr(copy.find("=") + 1, first.size());
        copy.erase(0, copy.find(";") + 1);

        if (header.MAGIC_NUMBER != std::stoi(second))
            return (false);
        first = copy.substr(0, copy.find(";"));
        second = first.substr(copy.find("=") + 1, first.size());
        copy.erase(0, copy.find(";") + 1);
        statusCode.code = std::stoi(second);
        first = copy.substr(0, copy.find(";"));
        second = first.substr(copy.find("=") + 1, first.size());
        copy.erase(0, copy.find(";") + 1);
        data = second;
    }
    catch (std::exception const &e)
    {
        Logger::log(Logger::WARNING, e.what());
        statusCode = StatusCode::CORRUPTED;
        return false;
    }
    return (true);
}

bool plazza::network::Packet::isCorrupted() const
{
    return statusCode == StatusCode::CORRUPTED;
}

bool plazza::network::Packet::isRequest() const
{
    return statusCode >= 700;
}

bool plazza::network::Packet::isResponse() const
{
    return statusCode < 700;
}
bool plazza::network::Packet::isQuery() const {
	return statusCode >= 600 && statusCode < 700;
}


