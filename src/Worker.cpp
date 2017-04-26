//
// Created by peau_c on 4/19/17.
//

#include <unistd.h>
#include <iostream>
#include <mutex>
#include "Worker.hpp"
#include "CmdParser.hpp"

void plazza::Worker::operator()() {
	command task;
	while (true) {
		std::unique_lock<std::mutex> lock(PoolRef.getQueueMutex());
		PoolRef.getAreThreadsFree().at(this->workerIndex) = true;
		while (!PoolRef.shouldStop() && !PoolRef.hasWork()) {
			PoolRef.getConditionVariable().wait(lock);
		}
		if (PoolRef.shouldStop()) //
			return;
		task = PoolRef.getFrontTask();
		PoolRef.getAreThreadsFree().at(this->workerIndex) = false;
		lock.unlock();
		sleep(1);
	}
}

plazza::Worker::Worker(plazza::ThreadPool &s, size_t index) : workerIndex(index), PoolRef(s) {}
