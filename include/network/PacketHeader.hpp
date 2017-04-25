//
// Created by Pierre Bougon on 24/04/17.
//

#ifndef CPP_PLAZZA_PACKETHEADER_HPP_
#define CPP_PLAZZA_PACKETHEADER_HPP_


#include "StatusCode.hpp"

namespace plazza
{
    namespace network
    {
        struct PacketHeader
        {
            PacketHeader();
            PacketHeader(PacketHeader const &other);
            PacketHeader &operator=(PacketHeader const &other);

            static constexpr int MAGIC_NUMBER = 0x42;
        };
    }
}


#endif // !CPP_PLAZZA_PACKETHEADER_HPP_
