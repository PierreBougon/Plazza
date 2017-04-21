//
// Created by peau_c on 4/19/17.
//

#include <unistd.h>
#include <iostream>
#include <mutex>
#include "Worker.hpp"

void plazza::Worker::operator()() {
	std::string task;
	while (true) {
		// Creation d'une scope pour release la mutex en sortie de scope
		{
			std::unique_lock<std::mutex> lock(PoolRef.getQueueMutex());
			
			// Si il n'y a pas de tasks, part en sleep
			while (!PoolRef.shouldStop() && PoolRef.getTasks().empty()) {
				PoolRef.getConditionVariable().wait(lock);
			}
			if (PoolRef.shouldStop()) //
				return;
			// recupere une task et l'enleve de le queue
			task = PoolRef.getTasks().front();
			PoolRef.popFrontTask();
		}
		//Partie execution
		std::cout << task << std::endl;
		sleep(1);
	}
}
