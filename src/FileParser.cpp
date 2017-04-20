//
// Created by sauvau_m on 4/17/17.
//

#include <fstream>
#include <iostream>
#include "FileParser.hpp"

plazza::FileParser::~FileParser() {
}

plazza::FileParser::FileParser() {
    expressions["email"] = std::regex("([\\w-\\.]+)@((?:[\\w]+\\.)+)([a-zA-Z]{2,4})");
    expressions["phone"] = std::regex("(?:(?:\\+|00)33|(\\b0))[ \\t]?[1-9](?:[ \\t]?\\d{2}){4}\\b");
    expressions["ip"] = std::regex("\\b(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\b");
}

void plazza::FileParser::feed(std::string const &str) {
    buffer += str;
}

void plazza::FileParser::reset() {
    buffer.clear();
}

std::vector<std::string> plazza::FileParser::find(std::string expr) {
    std::vector<std::string> result;
    std::smatch match;

    if (expressions.find(expr) != expressions.end()) {
        while (std::regex_search(buffer, match, expressions[expr])) {
            if (match.str() != "")
                result.push_back(match.str());
            buffer = match.suffix().str();
        }
    }
    return result;
}

void plazza::FileParser::open(std::string const &file) {
    std::ifstream ifs;

    reset();
    ifs.open(file);
    if (ifs.is_open()) {
        std::string buffer((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
        feed(buffer);
        ifs.close();
    }
}

std::vector<std::string> plazza::FileParser::getPhones() {
    return find("phone");
}

std::vector<std::string> plazza::FileParser::getEmails() {
    return find("email");
}

std::vector<std::string> plazza::FileParser::getIps() {
    return find("ip");
}