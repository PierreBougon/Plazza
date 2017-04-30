//
// Created by peau_c on 4/21/17.
//

#include <network/Client.hpp>
#include <unistd.h>
#include "sstream"
#include "Process.hpp"

plazza::Process::Process(size_t numberOfProcesses) : client(plazza::network::Client::getInstance()),
													 threadPool(numberOfProcesses) {
    baseTime = std::chrono::steady_clock::now();
	std::cerr << "Process CTOR" << std::endl;
	client.Init(4242, "127.0.0.1");
	client.connect();
	client.bind(std::bind((&plazza::Process::handleNewPackets), this, std::placeholders::_1));
	client.run();
	// TODO
}

plazza::Process::~Process() {
	client.stop();
}

bool plazza::Process::shouldQuit() const {
	return (threadPool.shouldStop());
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
	if (packet.isOther()) {
		if (tasks.size() == threadPool.getNumberOfThreads() * 2) {
			plazza::network::Packet outputPacket(plazza::network::StatusCode::INTERNAL_SERVER_ERROR);
			plazza::network::Client::getInstance().send(outputPacket,
														plazza::network::Client::getInstance().getSocket());
		}
	}
	
}

bool plazza::Process::isTimeout()
{
    if (threadPool.numberOfFreeThread() == threadPool.getNumberOfThreads())
    {
        std::chrono::duration<double> timeElapsed =
                std::chrono::duration_cast<std::chrono::duration<double>>
                        (std::chrono::steady_clock::now() - baseTime);
        std::cout << timeElapsed.count() << std::endl;
        // There s not a single thread which is working
        return timeElapsed.count() >= std::chrono::seconds(7).count();
    }
    else
    {
        // There is at least 1 thread working
        baseTime = std::chrono::steady_clock::now();
    }
    return false;
}
