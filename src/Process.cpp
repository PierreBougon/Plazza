//
// Created by peau_c on 4/21/17.
//

#include <network/Client.hpp>
#include <unistd.h>
#include "sstream"
#include "Process.hpp"

plazza::Process::Process(size_t numberOfProcesses) : client(plazza::network::Client::getInstance()),
													 threadPool(numberOfProcesses) {
	std::cerr << "je suis new thread" << std::endl;
	client.Init(4242, "127.0.0.1");
	std::cerr << "client trying to connect" << std::endl;
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
	std::cout << "Destructor process" << std::endl;
}

void plazza::Process::handleNewPackets(const plazza::network::Packet &packet) {
	std::string data;
	
	std::cout << "Je suis dans handleNewPackets" << std::endl;
	std::cout << "data" << packet.data << std::endl;
	sleep(3);
	if (packet.isQuery()) {
		std::stringstream stringstream;
		
		stringstream << std::to_string(threadPool.getNumberOfThreads());
		network::Packet packetToSend(network::StatusCode::OK, stringstream.str());
		
		client.send(packetToSend, client.getSocket());
	} else if (packet.isRequest()) {
		if (tasks.size() == threadPool.getNumberOfThreads() * 2) {;//TODO RENVOYER UN PACKET D'ERREUR
			plazza::network::Packet outputPacket(plazza::network::StatusCode::INTERNAL_SERVER_ERROR);
			plazza::network::Client::getInstance().send(outputPacket,
														plazza::network::Client::getInstance().getSocket());
			
		} else {
			std::string first = packet.data.substr(0, packet.data.find(" "));
			std::string second = packet.data.substr(packet.data.find(" ") + 1, packet.data.size());
			command cmd(first, static_cast<plazza::Information>(std::stoi(second)));
			threadPool.enqueue(cmd);
		}
	}
}
