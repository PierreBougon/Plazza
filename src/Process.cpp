//
// Created by peau_c on 4/21/17.
//

#include <network/Client.hpp>
#include "Process.hpp"
#include "CmdParser.hpp"

plazza::Process::Process(size_t numberOfProcesses) : threadPool(numberOfProcesses), client(plazza::network::Client().getInstance()){
	client.Init(4242, "localhost");
	client.connect();
	std::function<void (const plazza::network::Packet&)> function;
	client.bind(std::bind ((&plazza::Process::addNewTask), this, std::placeholders::_1));
}

plazza::Process::~Process() {

}

void plazza::Process::addNewTask(const plazza::network::Packet &packet) {
	std::string data;
	
	if (tasks.size() == threadPool.getNumberOfThreads() * 2) {
		;//TODO RENVOYER UN PACKET D'ERREUR
		plazza::network::Packet outputPacket(plazza::network::StatusCode::INTERNAL_SERVER_ERROR);
		plazza::network::Client().getInstance().send(outputPacket, plazza::network::Client().getInstance().getSocket());
	}
	std::string first = packet.data.substr(0, packet.data.find(" "));
	std::string second = packet.data.substr(packet.data.find(" ") + 1, packet.data.size());
	command cmd(first, static_cast<plazza::Information>(std::stoi(second)));
	threadPool.enqueue(cmd);
}
