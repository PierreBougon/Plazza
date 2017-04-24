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
#include "IMutex.hpp"


namespace plazza {
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
		void setStop(bool stop);
		
		std::string getFrontTask();
		std::vector<bool, std::allocator<bool>> &getAreThreadsFree();
		bool shouldStop() const;
		bool hasWork() const;
		
		//Utils
		void enqueue(std::string line);
	private:
		std::vector<bool> areThreadsFree;
		std::vector<std::thread> ThreadList;
		std::queue<std::string> tasks;
		std::mutex queue_mutex;
		std::condition_variable conditionVariable;
		bool stop;
	};
}

#endif //CPP_PLAZZA_THREADPOOL_HPP
