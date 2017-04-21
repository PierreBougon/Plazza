//
// Created by sauvau_m on 4/21/17.
//

#include "PlazzaError.hpp"

plazza::PlazzaError::~PlazzaError() throw() {

}

plazza::PlazzaError::PlazzaError(const std::string &msg) throw() : msg(msg)  {

}

const char *plazza::PlazzaError::what() const throw() {
    return msg.c_str();
}

plazza::CmdParserError::~CmdParserError() throw() {

}

plazza::CmdParserError::CmdParserError(const std::string &msg) throw() : PlazzaError(msg) {

}

