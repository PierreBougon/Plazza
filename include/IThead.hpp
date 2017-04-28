//
// Created by peau_c on 4/12/17.
//

#ifndef CPP_PLAZZA_ITHREAD_HPP
#define CPP_PLAZZA_ITHREAD_HPP

namespace plazza {
	class IThread {
		virtual void setIsFree(bool newState) = 0;
        virtual bool isFree() const = 0;
		virtual void join() = 0;
    };
}
#endif //CPP_PLAZZA_THEAD_HPP
