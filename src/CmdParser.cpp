//
// Created by sauvau_m on 4/18/17.
//

#include <algorithm>
#include "CmdParser.hpp"

plazza::CmdParser::~CmdParser() {

}

void plazza::CmdParser::feed(std::string const &str) {

    std::string tmp;
    std::unique_copy(str.begin(), str.end(), std::back_insert_iterator<std::string>(tmp),
                     [](char a, char b) { return isspace(a) && isspace(b); });
    tmp.erase(tmp.begin(), std::find_if(tmp.begin(), tmp.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    tmp.erase(std::find_if(tmp.rbegin(), tmp.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
              tmp.end());
    stream << tmp << std::endl;
}

std::unique_ptr<plazza::ast_node> plazza::CmdParser::parse() {
    std::unique_ptr<ast_node> root = std::make_unique<ast_node>(ast_node(nullptr));
    return root;
}

void plazza::CmdParser::reset() {
    stream.clear();
}
