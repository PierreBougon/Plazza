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

    enum ASTNodeType {
        ROOT,
        CMD,
        FILE,
        END_CMD,
        END,
    };

    enum Information {
        PHONE_NUMBER,
        EMAIL_ADDRESS,
        IP_ADDRESS,
    };

    struct ast_node {
        ast_node(std::vector<std::unique_ptr<ast_node>> children)
                : children(std::move(children)) {}
        ASTNodeType type;
        std::string value;
        std::vector<std::unique_ptr<ast_node>> children;
    };

    class CmdParser {

        size_t nbCmd;
        std::stringstream stream;
        void addNode(std::unique_ptr<ast_node> &root, ASTNodeType type, std::string const &value);
        void addNode(std::unique_ptr<ast_node> &root, std::string const & cmp);
        void addNodeFile(std::unique_ptr<ast_node> &root);
        void checkCmdIntegrity(ast_node *node);
        std::string trim(std::string const &str);
    public:
        virtual ~CmdParser();
        CmdParser();
        std::unique_ptr<ast_node> parse();
        void checkIntegrity(ast_node *node);
        void feed(std::string const &str);
        void reset();
        void dumpTree(ast_node *node);
        size_t getNbCmd();
    };
}

#endif //CPP_PLAZZA_CMDPARSER_HPP
