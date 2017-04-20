//
// Created by peau_c on 4/19/17.
//

#include <iostream>
#include "ThreadPool.hpp"
#include "Worker.hpp"

plazza::ThreadPool::ThreadPool(size_t numberOfThreads) : stop(false) {
	for(size_t i = 0; i < numberOfThreads; ++i) {
		ThreadList.push_back(std::thread(Worker(*this, i)));
	}
	enqueue("test01");
	enqueue("test02");
	enqueue("test03");
	enqueue("test04");
	enqueue("test05");
	enqueue("test06");
	enqueue("test07");
	enqueue("test08");
	enqueue("test09");
	enqueue("test10");
	enqueue("test11");
	enqueue("test12");
	enqueue("test13");
	enqueue("test14");
}

plazza::ThreadPool::~ThreadPool() {
	stop = true;
	conditionVariable.notify_all();
	
	for(size_t i = 0; i < ThreadList.size(); ++i) {
		ThreadList[i].join();
	}
}

void plazza::ThreadPool::enqueue(std::string line) {
	// La scope est la pour appeler le destructeur du unique_lock et au final unlock la mutex
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		tasks.push(line);
	}
	
	conditionVariable.notify_one();
}

std::string plazza::ThreadPool::getFrontTask() {
	std::string ret;
	ret = tasks.front();
	
	tasks.pop();
	return (ret);
}

std::queue<std::string> &plazza::ThreadPool::getTasks() {
	return tasks;
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