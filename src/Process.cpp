//
// Created by peau_c on 4/21/17.
//

#include <network/Client.hpp>
#include <unistd.h>
#include "sstream"
#include "Process.hpp"

plazza::Process::Process(size_t numberOfProcesses) : client(plazza::network::Client::getInstance()),
													 threadPool(numberOfProcesses) {
	std::cerr << "Process CTOR" << std::endl;
	client.Init(4242, "127.0.0.1");
	client.connect();
	client.bind(std::bind((&plazza::Process::handleNewPackets), this, std::placeholders::_1));
	client.run();
	network::Packet outputPacket;
	outputPacket.statusCode = 200;
	outputPacket.data = "CECI EST UN PENIS";
	client.send(outputPacket, client.getSocket());
	// TODO
}

plazza::Process::~Process() {
	client.stop();
}

void plazza::Process::handleNewPackets(const plazza::network::Packet &packet) {
	std::string data;
	
	if (packet.isQuery()) {
		if (packet.isTask()) {
			std::cout << "isTask" << std::endl;
			std::string first = packet.data.substr(0, packet.data.find(" "));
			std::string second = packet.data.substr(packet.data.find(" ") + 1, packet.data.size());
			std::cout << "first |" << first << "| second |" << second << "|" << std::endl;
			command cmd(first, static_cast<plazza::Information>(std::stoi(second)));
			std::cout << first << std::endl;
			threadPool.enqueue(cmd);
		} else {
			std::stringstream stringstream;
			
			stringstream << std::to_string(threadPool.numberOfFreeThread());
			network::Packet packetToSend(network::StatusCode::THREAD_COUNT, stringstream.str());
			
			client.send(packetToSend, client.getSocket());
		}
	}
	if (packet.isRequest()) {
		if (tasks.size() == threadPool.getNumberOfThreads() * 2) {
			plazza::network::Packet outputPacket(plazza::network::StatusCode::INTERNAL_SERVER_ERROR);
			plazza::network::Client::getInstance().send(outputPacket,
														plazza::network::Client::getInstance().getSocket());
		}
	}
	
}
