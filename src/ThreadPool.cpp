//
// Created by peau_c on 4/19/17.
//

#include <iostream>
#include "ThreadPool.hpp"
#include "Worker.hpp"


plazza::ThreadPool::ThreadPool(size_t numberOfThreads) : areThreadsFree(numberOfThreads), stop(false) {
	std::cout << "Tpool ctor" << std::endl;
	for(size_t i = 0; i < numberOfThreads; ++i) {
		ThreadList.push_back(new Thread(*this, i));
	}
	std::cout << "end of tpool ctor" << std::endl;
}

plazza::ThreadPool::~ThreadPool() {
	stop = true;
	conditionVariable.notify_all();
	
	for(size_t i = 0; i < ThreadList.size(); ++i) {
		ThreadList[i]->join();
	}
}

void plazza::ThreadPool::enqueue(command line) {
	std::unique_lock<std::mutex> lock(queue_mutex);
	tasks.push(line);
	lock.unlock();
	conditionVariable.notify_one();
}

plazza::command plazza::ThreadPool::getFrontTask() {
	command ret;
	
	ret = tasks.front();
	tasks.pop();
	
	return (ret);
}

bool plazza::ThreadPool::shouldStop() const {
	return stop;
}

void plazza::ThreadPool::setStop(bool stop) {
	this->stop = stop;
}

std::mutex &plazza::ThreadPool::getQueueMutex() {
	return queue_mutex;
}

std::condition_variable &plazza::ThreadPool::getConditionVariable() {
	return conditionVariable;
}

size_t plazza::ThreadPool::getNumberOfThreads() const {
	return ThreadList.size();
}

bool plazza::ThreadPool::hasWork() const {
	return (tasks.size() != 0);
}
size_t plazza::ThreadPool::numberOfFreeThread() const {
	size_t i = 0;
	for (auto it = areThreadsFree.begin(); it < areThreadsFree.end(); it++) {
		if (*it == true)
			i++;
	}
	return (i);
}
