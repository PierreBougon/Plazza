//
// Created by peau_c on 4/21/17.
//

#include <network/Client.hpp>
#include "Process.hpp"
#include "CmdParser.hpp"

plazza::Process::Process(size_t numberOfProcesses) : threadPool(numberOfProcesses) {
	plazza::network::Client().getInstance().Init(4242, "localhost");
	plazza::network::Client().getInstance().connect();
}

plazza::Process::~Process() {

}
void plazza::Process::addNewTask(const plazza::network::Packet &packet) {
	CmdParser parser;
	
	parser.feed(packet.data);
}
