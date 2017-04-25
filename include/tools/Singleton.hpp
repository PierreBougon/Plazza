//
// Created by Pierre Bougon on 25/04/17.
//

#ifndef CPP_PLAZZA_SINGLETON_HPP_
#define CPP_PLAZZA_SINGLETON_HPP_

template <typename T>
class Singleton
{
public:
    static T &getInstance()
    {
        static T instance;
        return instance;
    }
};

#endif // !CPP_PLAZZA_SINGLETON_HPP_
