//
// Created by peau_c on 4/19/17.
//

#ifndef CPP_PLAZZA_WORKER_HPP
#define CPP_PLAZZA_WORKER_HPP

#include "ThreadPool.hpp"

namespace plazza {
		class Worker {
		public:
			Worker(ThreadPool &s, size_t index);
			void operator()();
		private:
			size_t		workerIndex;
			ThreadPool &PoolRef;
		};
}

#endif //CPP_PLAZZA_WORKER_HPP
