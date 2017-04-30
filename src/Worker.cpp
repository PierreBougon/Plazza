//
// Created by peau_c on 4/19/17.
//

#include <unistd.h>
#include <iostream>
#include <mutex>
#include <network/Client.hpp>
#include <network/StaticSend.hpp>
#include "Worker.hpp"
#include "CmdParser.hpp"

void plazza::Worker::operator()() {
	command task;
	while (true) {
		std::vector<std::string> find;
		std::vector<std::string> res;
		threadRef.setIsFree(true);
		threadRef.lock();
		while (!threadRef.shouldStop() && !threadRef.hasWork()) {
			threadRef.wait();
		}
		if (threadRef.shouldStop()) //
			return;
		task = threadRef.getWork();
		threadRef.unlock();
		fileParser.reset();
		fileParser.open(task.file);
		if (task.information == PHONE_NUMBER) {
			find = fileParser.getPhones();
			res.insert(res.end(), find.begin(), find.end());
		}
		if (task.information == EMAIL_ADDRESS) {
			find = fileParser.getEmails();
			res.insert(res.end(), find.begin(), find.end());
		}
		if (task.information == IP_ADDRESS) {
			find = fileParser.getIps();
			res.insert(res.end(), find.begin(), find.end());
		}
        StaticSend::sendResult(res);
		threadRef.setIsFree(false);
	}
}

plazza::Worker::Worker(plazza::Thread &s, size_t index) : workerIndex(index), threadRef(s) {
}
