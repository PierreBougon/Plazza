//
// Created by sauvau_m on 4/17/17.
//

#ifndef CPP_PLAZZA_PARSER_HPP
#define CPP_PLAZZA_PARSER_HPP

#include <regex>
#include <string>

namespace plazza {

    class Parser {

        std::string buffer;
        std::regex expression;
        std::regex_constants::match_flag_type flags;
        Parser() = delete;

    public:
        virtual ~Parser();
        Parser(std::regex regex);
        Parser(std::regex regex, std::regex_constants::match_flag_type flags);
        void open(std::string const &file);
        void feed(std::string const &str);
        void reset();
        std::vector<std::string> find();

        static const Parser Email;
        static const Parser PhoneNumber;
        static const Parser IPAddress;
    };
}


#endif //CPP_PLAZZA_PARSER_HPP
