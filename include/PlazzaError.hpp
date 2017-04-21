//
// Created by sauvau_m on 4/21/17.
//

#ifndef CPP_PLAZZA_PLAZZAEXCEPTION_HPP
#define CPP_PLAZZA_PLAZZAEXCEPTION_HPP

#include <exception>
#include <string>

namespace plazza {

    class PlazzaError : public std::exception {
        std::string msg;
    public:
        virtual ~PlazzaError() throw();
        PlazzaError(const std::string &msg) throw();
        virtual const char *what() const throw();
    };

    class CmdParserError : public PlazzaError {
    public:
        virtual ~CmdParserError() throw();
        CmdParserError(const std::string &msg) throw();
    };
}


#endif //CPP_PLAZZA_PLAZZAEXCEPTION_HPP
