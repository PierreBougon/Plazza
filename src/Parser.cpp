//
// Created by sauvau_m on 4/17/17.
//

#include <fstream>
#include <iostream>
#include "Parser.hpp"

const plazza::Parser plazza::Parser::Email(std::regex("([\\w-\\.]+)@((?:[\\w]+\\.)+)([a-zA-Z]{2,4})"));
const plazza::Parser plazza::Parser::PhoneNumber(
        std::regex("(?:(?:\\+|00)33|(\\b0))[ \\t]?[1-9](?:[ \\t]?\\d{2}){4}\\b"));
const plazza::Parser plazza::Parser::IPAddress(std::regex(
        "\\b(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\b"));

plazza::Parser::~Parser() {

}

plazza::Parser::Parser(std::regex regex) : expression(regex), flags(std::regex_constants::match_default) {
}

plazza::Parser::Parser(std::regex regex, std::regex_constants::match_flag_type flags) : expression(regex),
                                                                                        flags(flags) {

}

void plazza::Parser::feed(std::string const &str) {
    buffer += str;
}

void plazza::Parser::reset() {
    buffer.clear();
}

std::vector<std::string> plazza::Parser::find() {
    std::vector<std::string> result;
    std::smatch match;

    while (std::regex_search(buffer, match, expression, flags)) {
        if (match.str() != "")
            result.push_back(match.str());
        buffer = match.suffix().str();
    }
    return result;
}

void plazza::Parser::open(std::string const &file) {
    std::ifstream ifs;

    reset();
    ifs.open(file);
    if (ifs.is_open()) {
        std::string buffer((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
        feed(buffer);
        ifs.close();
    }
}

