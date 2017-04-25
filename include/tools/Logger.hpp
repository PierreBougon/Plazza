//
// Created by Pierre Bougon on 03/02/17.
//

#ifndef ARCADE_LOGGER_HPP_
#define ARCADE_LOGGER_HPP_


#include <string>

namespace Debug
{
    extern bool DEBUG_MODE;
}

class Logger
{
public:

    enum Level
    {
        Debug = 0,
        Info,
        Warning,
        Error,
    };

    static void log(Level lvl, std::string msg, bool abort = false);
};


#endif // !ARCADE_LOGGER_HPP_
