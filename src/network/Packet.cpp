//
// Created by Pierre Bougon on 23/04/17.
//

#include <PlazzaError.hpp>
#include <iostream>
#include <tools/Logger.hpp>
#include <socket/ASocket.hpp>
#include <cmath>
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
        Logger::log(Logger::DEBUG, "deserialize");

        std::string copy = serialized;

        std::string first = copy.substr(0, copy.find(";"));
        std::string second = first.substr(copy.find("=") + 1, first.size());
        copy.erase(0, copy.find(";") + 1);

        Logger::log(Logger::DEBUG, "deserialize magic nbr : " + second);
        if (header.MAGIC_NUMBER != std::stoi(second))
            return (false);
        first = copy.substr(0, copy.find(";"));
        second = first.substr(copy.find("=") + 1, first.size());
        copy.erase(0, copy.find(";") + 1);
        Logger::log(Logger::DEBUG, "deserialize statusCode : " + second);
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
        return (false);
    }
    return (true);
}

bool plazza::network::Packet::isCorrupted() const
{
    return statusCode == StatusCode::CORRUPTED;
}

bool plazza::network::Packet::isOther() const
{
    return statusCode >= 700 && statusCode < 800;
}

bool plazza::network::Packet::isResponse() const
{
    return statusCode >= 200 && statusCode < 700;
}

bool plazza::network::Packet::isQuery() const {
	return statusCode >= 600 && statusCode < 700;
}

bool plazza::network::Packet::isSpecific() const
{
    return statusCode >= 100 && statusCode < 200;
}

bool plazza::network::Packet::isTooLarge() const
{
    return serialize().size() > ASocket::BUFFER_SIZE;
}

std::vector<plazza::network::Packet> plazza::network::Packet::dividePacket() const
{
    Packet basePacket = *this;
    std::vector<Packet> listPacket;
    size_t nbPacket = static_cast<size_t>(std::ceil(getDataSize() / getMaxDataSize()));
    size_t offset = 0;

    for (size_t i = 0; i < nbPacket; ++i)
    {
        basePacket.data = this->data.substr(offset, getMaxDataSize());
        listPacket.emplace_back(basePacket);
        offset += getMaxDataSize();
    }

    return std::move(listPacket);
}

size_t plazza::network::Packet::getDataSize() const
{
    return serialize().size() - serialize().find_last_of("=") + 1;
}

size_t plazza::network::Packet::getMaxDataSize() const
{
    return ASocket::BUFFER_SIZE - serialize().find_last_of("=") + 1;
}


