//
// Created by peau_c on 4/19/17.
//

#include <iostream>
#include "ThreadPool.hpp"
#include "Worker.hpp"

ThreadPool::ThreadPool(int numberOfThreads) : stop(false) {
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

ThreadPool::~ThreadPool() {
	stop = true;
	conditionVariable.notify_all();
	
	for (int i = 0; i < ThreadList.size(); ++i) {
		ThreadList[i].join();
	}
}

void ThreadPool::enqueue(std::string line)
{
	// La scope est la pour appeler le destructeur du unique_lock et au final unlock la mutex
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		tasks.push(line);
	}
	
	conditionVariable.notify_one();
}

std::vector<std::thread> &ThreadPool::getThreadList() {
	return ThreadList;
}
void ThreadPool::popFrontTask() {
	tasks.pop();
}
std::queue<std::string> &ThreadPool::getTasks() {
	return tasks;
}
void ThreadPool::setTasks(const std::queue<std::string> &tasks) {
	this->tasks = tasks;
}
bool ThreadPool::shouldStop() const {
	return stop;
}
void ThreadPool::setStop(bool stop) {
	this->stop = stop;
}

std::mutex &ThreadPool::getQueueMutex() {
	return queue_mutex;
}

std::condition_variable &ThreadPool::getConditionVariable() {
	return conditionVariable;
}
