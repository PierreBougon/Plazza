//
// Created by Pierre Bougon on 03/02/17.
//

#ifndef ARCADE_LOGGER_HPP_
#define ARCADE_LOGGER_HPP_

#include <fstream>
#include <string>
#include "Singleton.hpp"

namespace Debug
{
    extern bool DEBUG_MODE;
}

class Logger : public Singleton<Logger>
{
    friend class Singleton<Logger>;

    std::ofstream outFile;
    Logger(const Logger&) = delete;
    virtual ~Logger();
    Logger();

public:
    enum Level
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    void setFile(std::string const &file);
    void closeFile();
    static void log(Level lvl, std::string msg, bool abort = false);
    void log(std::string msg, Level lvl = INFO);
    void logFile(std::string msg, Level lvl = INFO);
    std::string toString(Level lvl);
};


#endif // !ARCADE_LOGGER_HPP_
