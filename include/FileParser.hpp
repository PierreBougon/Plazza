//
// Created by sauvau_m on 4/17/17.
//

#ifndef CPP_PLAZZA_PARSER_HPP
#define CPP_PLAZZA_PARSER_HPP

#include <regex>
#include <string>
#include <unordered_map>

namespace plazza {

    class FileParser {

        std::string buffer;
        std::unordered_map<std::string, std::regex> expressions;

    public:
        virtual ~FileParser();
        FileParser();
        void open(std::string const &file);
        void feed(std::string const &str);
        void reset();
        std::vector<std::string> find(std::string expr);
        std::vector<std::string> getPhones();
        std::vector<std::string> getEmails();
        std::vector<std::string> getIps();
    };
}

#endif //CPP_PLAZZA_PARSER_HPP
