//
// Created by peau_c on 4/21/17.
//

#ifndef CPP_PLAZZA_PROCESS_HPP
#define CPP_PLAZZA_PROCESS_HPP

#include "FileParser.hpp"
#include "ThreadPool.hpp"
#include "IProcess.hpp"

namespace plazza {
	class Process : public IProcess {
	public:
		Process(size_t);
		~Process();
	private:
		ThreadPool	threadPool;
		FileParser	fileParser;
	};
}

#endif //CPP_PLAZZA_PROCESS_HPP
