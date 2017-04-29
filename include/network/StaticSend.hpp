//
// Created by sauvau_m on 4/29/17.
//

#ifndef CPP_PLAZZA_PACKETUTILITY_HPP
#define CPP_PLAZZA_PACKETUTILITY_HPP

#include <string>
#include <vector>

namespace plazza {
    class StaticSend {
    public:
        static std::string sendResult(std::vector<std::string> const &vector);
    };
}

#endif //CPP_PLAZZA_PACKETUTILITY_HPP
