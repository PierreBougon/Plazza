//
// Created by Pierre Bougon on 23/04/17.
//

#ifndef CPP_PLAZZA_PACKET_HPP_
#define CPP_PLAZZA_PACKET_HPP_


#include <cstddef>
#include "StatusCode.hpp"
#include "PacketHeader.hpp"
#include "ISerializable.hpp"

namespace plazza
{
    namespace network
    {
        struct Packet : public ISerializable
        {
            Packet();
            Packet(StatusCode const &statusCode, std::string _data = "");
            Packet(Packet const &other);
            Packet &operator=(Packet const &other);

            network::PacketHeader           header;
            StatusCode                      statusCode;
            std::string                     data;

            std::string     serialize() const override;
            bool            deserialize(std::string const &serialized) const override;


            // Basic packet
            static const Packet OK;
            static const Packet BAD_REQUEST;
            static const Packet INTERNAL_SERVER_ERROR;

            static const Packet ACCEPTED;
            static const Packet FORBIDDEN;
        };
    }
}


#endif // !CPP_PLAZZA_PACKET_HPP_
