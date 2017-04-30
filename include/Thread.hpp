//
// Created by peau_c on 4/27/17.
//

#ifndef CPP_PLAZZA_THREAD_HPP
#define CPP_PLAZZA_THREAD_HPP

#include "ThreadPool.hpp"
#include "IThead.hpp"

namespace plazza {
	class ThreadPool;
	
	class Thread : public IThread {
	public:
		Thread(ThreadPool& threadPoolRef, size_t threadId);
		~Thread();
		virtual command getItemFromQueue();
		command getWork();
		virtual void join();

		bool shouldStop() const;
		void lock();
		void unlock();
		bool isFree() const override;
		void setIsFree(bool newState);
		void wait();
		bool hasWork() const;
	private:
		bool _isLocked;
		std::unique_lock<std::mutex> _lock;
		ThreadPool	&threadPool;
		size_t threadId;
		std::thread	thread;
		std::atomic<bool> _isFree;
	};
	
}

#endif //CPP_PLAZZA_THREAD_HPP
