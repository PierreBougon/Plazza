//
// Created by peau_c on 4/19/17.
//

#include <iostream>
#include "ThreadPool.hpp"
#include "Worker.hpp"

plazza::ThreadPool::ThreadPool(int numberOfThreads) : stop(false) {
	for(int i = 0; i < numberOfThreads; ++i) {
		ThreadList.push_back(std::thread(Worker(*this)));
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
	
	for (int i = 0; i < ThreadList.size(); ++i) {
		ThreadList[i].join();
	}
}

void plazza::ThreadPool::enqueue(std::string line)
{
	// La scope est la pour appeler le destructeur du unique_lock et au final unlock la mutex
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		tasks.push(line);
	}
	
	conditionVariable.notify_one();
}

std::vector<std::thread> &plazza::ThreadPool::getThreadList() {
	return ThreadList;
}

void plazza::ThreadPool::popFrontTask() {
	tasks.pop();
}

std::queue<std::string> &plazza::ThreadPool::getTasks() {
	return tasks;
}

void plazza::ThreadPool::setTasks(const std::queue<std::string> &tasks) {
	this->tasks = tasks;
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
