//
// Created by peau_c on 4/19/17.
//

#ifndef CPP_PLAZZA_WORKER_HPP
#define CPP_PLAZZA_WORKER_HPP

#include "ThreadPool.hpp"

namespace plazza {

    class Worker {
    public:
        Worker(ThreadPool &s) : PoolRef(s) {};
        void operator()();

    private:
        ThreadPool &PoolRef;
    };
}

#endif //CPP_PLAZZA_WORKER_HPP
