//
// Created by peau_c on 4/12/17.
//

#ifndef CPP_PLAZZA_IMUTEX_HPP
#define CPP_PLAZZA_IMUTEX_HPP

namespace plazza {
	class IMutex {
	public:
		virtual void lock() = 0;
		virtual void unlock() = 0;
	};
}
#endif //CPP_PLAZZA_IMUTEX_HPP
