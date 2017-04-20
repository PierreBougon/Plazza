//
// Created by sauvau_m on 4/18/17.
//

#ifndef CPP_PLAZZA_CMDPARSER_HPP
#define CPP_PLAZZA_CMDPARSER_HPP

#include <string>
#include <vector>
#include <sstream>
#include <memory>

namespace plazza {

    enum Information {
        PHONE_NUMBER,
        EMAIL_ADDRESS,
        IP_ADDRESS
    };

    struct ast_node {
        ast_node(std::vector<std::unique_ptr<ast_node>> *children)
                : children(children) {}

        Information type;
        std::string value;
        std::vector<std::unique_ptr<ast_node>> *children;
    };

    class CmdParser {

        std::stringstream stream;

    public:
        virtual ~CmdParser();
        std::unique_ptr<ast_node> parse();
        void feed(std::string const &str);
        void reset();
    };
}

#endif //CPP_PLAZZA_CMDPARSER_HPP
