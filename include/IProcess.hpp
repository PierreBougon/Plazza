//
// Created by peau_c on 4/12/17.
//

#ifndef CPP_PLAZZA_PROCESSES_HPP
#define CPP_PLAZZA_PROCESSES_HPP

#include <vector>
#include <string>


namespace plazza {

	class IProcess {
		virtual std::vector<bool> isBusy() const = 0;

		virtual bool isFull() const = 0;

		virtual bool feed(std::string const &) = 0;

	};
}
#endif //CPP_PLAZZA_PROCESSES_HPP
