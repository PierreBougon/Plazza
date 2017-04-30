//
// Created by peau_c on 4/27/17.
//

#include <iostream>
#include "Thread.hpp"
#include "ThreadPool.hpp"
#include "Worker.hpp"

plazza::Thread::Thread(ThreadPool &threadPool, size_t threadId) : threadPool(threadPool), threadId(threadId) {
	thread = std::thread(Worker(*this, threadId));
}

plazza::Thread::~Thread() {

}

bool plazza::Thread::isFree() const {
	return _isFree;
}

void plazza::Thread::wait() {
	threadPool.getConditionVariable().wait(_lock);
}

void plazza::Thread::join() {
	thread.join();
}
void plazza::Thread::setIsFree(bool newState) {
	_isFree = newState;
}

void plazza::Thread::lock() {
	_lock = std::unique_lock<std::mutex>(threadPool.getQueueMutex());
	_isLocked = true;
}

void plazza::Thread::unlock() {
	_lock.unlock();
	_isLocked = false;
}

plazza::command plazza::Thread::getWork() {
	return threadPool.getFrontTask();
}

bool plazza::Thread::shouldStop() const {
	return threadPool.shouldStop();
}

bool plazza::Thread::hasWork() const {
	return threadPool.hasWork();
}
plazza::command plazza::Thread::getItemFromQueue() {
	return (threadPool.getFrontTask());
}
