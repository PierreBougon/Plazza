//
// Created by sauvau_m on 4/29/17.
//

#include <network/Client.hpp>
#include "network/StaticSend.hpp"

std::string plazza::StaticSend::sendResult(std::vector<std::string> const &vector) {
    std::string data;

    for (size_t i = 0; i < vector.size(); ++i) {
        data += vector[i];
        if (i != vector.size() - 1)
        data += "\n";
    }
    network::Client::getInstance().send(network::Packet(network::StatusCode::RESULT, data), network::Client::getInstance().getSocket());
    return (std::move(data));
}
