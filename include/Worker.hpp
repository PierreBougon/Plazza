//
// Created by peau_c on 4/19/17.
//

#ifndef CPP_PLAZZA_WORKER_HPP
#define CPP_PLAZZA_WORKER_HPP

#include "Thread.hpp"
#include "FileParser.hpp"

namespace plazza {
		class Worker {
		public:
			Worker(Thread &s, size_t index);
			void operator()();
		private:
			FileParser  fileParser;
			size_t		workerIndex;
			Thread		&threadRef;
		};
}

#endif //CPP_PLAZZA_WORKER_HPP
