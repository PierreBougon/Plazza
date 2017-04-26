//
// Created by peau_c on 4/26/17.
//

#ifndef CPP_PLAZZA_IPROCESSHANDLER_HPP
#define CPP_PLAZZA_IPROCESSHANDLER_HPP

#include "CmdParser.hpp"

namespace plazza {
	class IProcessHandler {
	public:
		virtual void feed(const std::vector<command> &commandList) = 0;
	};
}

#endif //CPP_PLAZZA_IPROCESSHANDLER_HPP
