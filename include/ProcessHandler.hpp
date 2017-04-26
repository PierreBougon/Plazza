//
// Created by peau_c on 4/26/17.
//

#ifndef CPP_PLAZZA_PROCESSHANDLER_HPP
#define CPP_PLAZZA_PROCESSHANDLER_HPP

#include "IProcessHandler.hpp"
#include "CmdParser.hpp"

namespace plazza {
	class ProcessHandler : public IProcessHandler {
	public:
		ProcessHandler(bool isClient, size_t numberOfThreads);
		~ProcessHandler();
	};
}


#endif //CPP_PLAZZA_PROCESSHANDLER_HPP
