//
// Created by Pierre Bougon on 20/04/17.
//

#include <exceptions/SocketError.hpp>
#include <cstring>
#include <tools/Logger.hpp>
#include <iostream>
#include <bits/sigthread.h>
#include <bits/signum.h>
#include <signal.h>
#include <csignal>
#include "socket/TCPClient.hpp"

plazza::network::TCPClient::TCPClient(uint16_t port, const std::string &hostname) : ASocket(port, hostname)
{}

plazza::network::Packet plazza::network::TCPClient::receive(sock_t socket)
{
    network::Packet inputPacket;

    std::string     data;
    char            buf[BUFFER_SIZE];
    ssize_t         ret;

    ret = ::recv(socket, buf, BUFFER_SIZE, 0);
    if (ret == -1 && errno == EINTR)
    {
        // Stopping Client
        inputPacket.statusCode = StatusCode::NOTHING;
    }
    else if (ret == -1)
        throw SocketError("Cannot receive");
    else if (ret == 0)
        inputPacket.statusCode = StatusCode::CORRUPTED;
    else
        data += buf;

    inputPacket.deserialize(data);
    Logger::log(Logger::DEBUG, "Client Receiving: " + inputPacket.serialize());
    return std::move(inputPacket);
}

void plazza::network::TCPClient::send(const plazza::network::Packet &packet, plazza::network::sock_t socket)
{
    std::string data;

    if (!packet.isTooLarge())
    {
        data = packet.serialize();
        Logger::log(Logger::DEBUG, "Client Sending: " + data);
        if (::send(socket, data.c_str(), data.size(), 0) == -1)
            throw network::SocketError("Cannot send to the socket");
    }
    else
    {
        std::vector<Packet> listPacket = packet.dividePacket();
        for (std::vector<Packet>::iterator it = listPacket.begin(); it != listPacket.end(); ++it)
        {
            data = it->serialize();
            Logger::log(Logger::DEBUG, "Client Sending: " + data);
            if (::send(socket, data.c_str(), data.size(), 0) == -1)
                throw network::SocketError("Cannot send to the socket");
        }
    }
}

void plazza::network::TCPClient::connect()
{
	Logger::log(Logger::DEBUG, "Connect");
    _server = ::gethostbyname(_hostname.c_str());
    if (!_server)
        throw network::SocketError("No such host");
    //TODO
    ::bcopy((char *)_server->h_addr_list[0], (char *)&_servAddr.sin_addr.s_addr, static_cast<size_t >(_server->h_length));
    std::cerr << "sock: " << _socket << "_servaddr: " << _servAddr.sin_port << " " << _servAddr.sin_family << " " << _servAddr.sin_addr.s_addr << std::endl;
    if (::connect(_socket, (sockaddr *)(&_servAddr), sizeof(_servAddr)) == -1)
        throw network::SocketError("Cannot connect to server");
}

void plazza::network::TCPClient::run()
{
	Logger::log(Logger::DEBUG, "client running");
	if (_running || _thread.joinable())
    {
        Logger::log(Logger::WARNING, "Client is already running");
        return;
    }
    // todo check out thread launching

    _running = true;
    _mutex.lock();
    _thread = std::thread(&TCPClient::_core, this);
}

void plazza::network::TCPClient::_core()
{
    network::Packet packet;

    while (_running)
    {
        packet = receive(_socket);
        if (!packet.isCorrupted() && packet.statusCode != StatusCode::NOTHING)
            _onReceive(packet);
    }
    _mutex.unlock();
}

plazza::network::TCPClient::~TCPClient()
{
}

void plazza::network::TCPClient::stop()
{
    if (!_thread.joinable())
        return;
    _running = false;
    ::shutdown(_socket, SHUT_RD);
    _thread.join();
    Logger::log(Logger::DEBUG, "Stop client");
}

void plazza::network::TCPClient::wait()
{
    while (_running)
        std::this_thread::sleep_for(std::chrono::milliseconds(100000));
}

