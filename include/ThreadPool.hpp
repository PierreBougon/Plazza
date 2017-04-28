//
// Created by peau_c on 4/19/17.
//

#ifndef CPP_PLAZZA_THREADPOOL_HPP
#define CPP_PLAZZA_THREADPOOL_HPP

#include <atomic>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "CmdParser.hpp"
#include "Thread.hpp"


namespace plazza {
	class Thread;
	class ThreadPool {
	public:
		//CTOR DTOR
		ThreadPool(size_t numberOfThreads);
		~ThreadPool();
		
		//Setters
		void setStop(bool stop);
		
		//Getters
		size_t getNumberOfThreads() const;
		std::mutex &getQueueMutex();
		std::condition_variable &getConditionVariable();
		bool shouldStop() const;
		
		command getFrontTask();
		const std::vector<std::atomic<bool>> &getAreThreadsFree() const;
		bool hasWork() const;
		
		//Queueing
		void enqueue(command line);
	private:
		std::vector<std::atomic<bool>> areThreadsFree;
		std::vector<Thread*> ThreadList;
		std::queue<command> tasks;
		std::mutex queue_mutex;
		std::condition_variable conditionVariable;
		bool stop;
	};
}

#endif //CPP_PLAZZA_THREADPOOL_HPP
