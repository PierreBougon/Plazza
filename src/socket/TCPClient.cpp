//
// Created by Pierre Bougon on 20/04/17.
//

#include <exceptions/SocketError.hpp>
#include <cstring>
#include <tools/Logger.hpp>
#include "socket/TCPClient.hpp"

plazza::network::TCPClient::TCPClient(uint16_t port, const std::string &hostname) : ASocket(_port, _hostname)
{}

Packet plazza::network::TCPClient::receive(sock_t socket)
{
    network::Packet recvPacket;
    char buf[BUFFER_SIZE];


    // TODO loop to recv
    if (::recv(_socket, buf, BUFFER_SIZE, 0) < 0)
        throw network::SocketError("Cannot receive from socket");
    std::string data(buf);
    recvPacket.deserialize(data);
    return std::move(recvPacket);
}

void plazza::network::TCPClient::send(const plazza::network::Packet &packet, plazza::network::sock_t socket) const
{
    std::string data = packet.serialize();

    if (::send(socket, data.c_str(), data.size(), 0) == -1)
        throw network::SocketError("Cannot send to the socket");
}

// TODO move this to client
void plazza::network::TCPClient::connect()
{
    _server = gethostbyname(_hostname.c_str());
    if (!_server)
        throw network::SocketError("No such host");
    std::memmove(_server->h_addr_list[0], &_servAddr.sin_addr.s_addr, static_cast<size_t >(_server->h_length));
    if (::connect(_socket, static_cast<sockaddr *>(_servAddr), sizeof(_servAddr)) == -1)
        throw network::SocketError("Cannot connect to server");
}

void plazza::network::TCPClient::run()
{
    if (_running)
    {
        Logger::log(Logger::Warning, "Client is already running");
        return;
    }
    // todo check out thread launching

    _mutex.lock();
    _thread = std::thread(&_core);
}

void plazza::network::TCPClient::_core()
{
    network::Packet packet;

    while (_running)
    {
        packet = receive(_socket);
        onReceive(packet);
    }
    _mutex.unlock();
}

plazza::network::TCPClient::~TCPClient()
{

}