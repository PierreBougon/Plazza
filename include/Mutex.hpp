//
// Created by peau_c on 4/21/17.
//

#ifndef CPP_PLAZZA_MUTEX_HPP
#define CPP_PLAZZA_MUTEX_HPP

#include <mutex>
#include "IMutex.hpp"

namespace plazza {
	
	class Mutex : public IMutex {
	public:
		Mutex();
		~Mutex();
		void lock() override;
		void unlock() override;
	private:
		std::mutex mutex;
	};
}

#endif //CPP_PLAZZA_MUTEX_HPP
