//
// Created by peau_c on 4/19/17.
//

#ifndef CPP_PLAZZA_THREADPOOL_HPP
#define CPP_PLAZZA_THREADPOOL_HPP

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "IMutex.hpp"
#include "IConditionVariable.hpp"

class ThreadPool {
public:
	ThreadPool(int numberOfThreads);
	~ThreadPool();
protected:
public:
	std::vector<std::thread> &getThreadList();
	std::mutex &getQueueMutex();
	std::condition_variable &getConditionVariable();
	bool shouldStop() const;
	void setStop(bool stop);
	
	void popFrontTask();
	std::queue<std::string> &getTasks();
	void setTasks(const std::queue<std::string> &tasks);
	void enqueue(std::string line);
private:
	std::vector<std::thread>	ThreadList;
	std::queue<std::string>		tasks;
	std::mutex 					queue_mutex;
	std::condition_variable		conditionVariable;
	bool 						stop;
};

#endif //CPP_PLAZZA_THREADPOOL_HPP
