//
// Created by Pierre Bougon on 23/04/17.
//

#ifndef CPP_PLAZZA_PACKET_HPP_
#define CPP_PLAZZA_PACKET_HPP_


#include <cstddef>
#include <vector>
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
            Packet(StatusCode const &_statusCode, std::string _data = "");
            Packet(Packet const &other);
            Packet &operator=(Packet const &other);

            std::string     serialize() const override;
            bool            deserialize(std::string const &serialized) override;

			bool isQuery() const;
            bool isCorrupted() const;
            bool isSpecific() const;
            bool isOther() const;
            bool isResponse() const;
            bool isTooLarge() const;
			bool isTask() const;
			bool isThreadCount() const;

            std::vector<Packet> dividePacket() const;
            size_t              getDataSize() const;

            network::PacketHeader           header;
            StatusCode                      statusCode;
            std::string                     data;


            // Basic packet
            static const Packet OK;
            static const Packet BAD_REQUEST;
            static const Packet INTERNAL_SERVER_ERROR;

			static const Packet THREAD_COUNT;
            static const Packet ACCEPTED;
            static const Packet FORBIDDEN;
    
            static const Packet QUERY;
    
            static const Packet NOTHING;

            size_t getMaxDataSize() const;
		};
    }
}


#endif // !CPP_PLAZZA_PACKET_HPP_
