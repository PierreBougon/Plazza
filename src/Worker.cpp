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
		threadRef.setIsFree(true);
		threadRef.lock();
		//while (!threadRef.shouldStop() && !threadRef.hasWork()) {
		//	threadRef.getConditionVariable().wait(lock);
		//}
		if (threadRef.shouldStop()) //
			return;
		task = threadRef.getWork();
		threadRef.unlock();
		sleep(1);
		threadRef.setIsFree(false);
	}
}

plazza::Worker::Worker(plazza::Thread &s, size_t index) : workerIndex(index), threadRef(s) {}
