//
// Created by sauvau_m on 4/18/17.
//

#include <algorithm>
#include <iostream>
#include <PlazzaError.hpp>
#include "CmdParser.hpp"

plazza::CmdParser::~CmdParser() {

}

plazza::CmdParser::CmdParser() : nbCmd(0) {}

void plazza::CmdParser::feed(std::string const &str) {
    stream << trim(str) << std::endl;
}

std::string plazza::CmdParser::trim(std::string const &str) {
    std::string tmp;
    std::unique_copy(str.begin(), str.end(), std::back_insert_iterator<std::string>(tmp),
                     [](char a, char b) { return isspace(a) && isspace(b); });
    tmp.erase(tmp.begin(), std::find_if(tmp.begin(), tmp.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    tmp.erase(std::find_if(tmp.rbegin(), tmp.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
              tmp.end());
    return tmp;
}

std::unique_ptr<plazza::ast_node> plazza::CmdParser::parse() {
    std::unique_ptr<ast_node> root = std::make_unique<ast_node>(ast_node(std::vector<std::unique_ptr<ast_node>>(0)));
    root->type = ASTNodeType::ROOT;
    root->value = "root";
    std::string str;
    while (!stream.eof()) {
        std::unique_ptr<ast_node> node = std::make_unique<ast_node>(
                ast_node(std::vector<std::unique_ptr<ast_node>>(0)));
        node->type = ASTNodeType::CMD;
        node->value = "CMD";
        addNodeFile(node);
        if (!stream.eof())
            root->children.push_back(std::move(node));
    }
    addNode(root, ASTNodeType::END_CMD, "END");
    return std::move(root);
}

void plazza::CmdParser::reset() {
    nbCmd = 0;
    stream.clear();
}

void plazza::CmdParser::addNode(std::unique_ptr<plazza::ast_node> &root, plazza::ASTNodeType type,
                                std::string const &value) {
    std::unique_ptr<ast_node> node = std::make_unique<ast_node>(ast_node(std::vector<std::unique_ptr<ast_node>>(0)));
    node->type = type;
    node->value = value;
    root->children.push_back(std::move(node));
}

void plazza::CmdParser::addNodeFile(std::unique_ptr<plazza::ast_node> &node) {

    std::string str;
    while (!stream.eof()) {
        int input_char = stream.get();
        if (input_char == ' ' && str != "") {
            addNode(node, ASTNodeType::FILE, str);
            str.clear();
        } else if (input_char == 'P') {
            addNode(node, "PHONE_NUMBER");
            break;
        } else if (input_char == 'E') {
            addNode(node, "EMAIL_ADDRESS");
            break;
        } else if (input_char == 'I') {
            addNode(node, "IP_ADDRESS");
            break;
        } else if (isprint(input_char) && !isblank(input_char)) {
            str += input_char;
        }
    }
    if (!str.empty()) {
        throw plazza::CmdParserError("Unknown Command starting with " + str);
    }
}

void plazza::CmdParser::addNode(std::unique_ptr<plazza::ast_node> &root, std::string const &cmp) {
    std::string str;
    int input_char = stream.get();

    str += cmp[0];
    while (!stream.eof() && input_char != ';' && input_char != '\n') {
        str += input_char;
        input_char = stream.get();
    }
    str = trim(str);
    if (str != cmp)
        throw plazza::CmdParserError("Unknown Command starting with " + str);
    addNode(root, ASTNodeType::CMD, str);
    ++nbCmd;
    addNode(root, ASTNodeType::END_CMD, ";");
}

void plazza::CmdParser::dumpTree(plazza::ast_node *root) {
    if (root) {
        std::cout << root->type << " " << root->value << std::endl;
        for (size_t i = 0; i < root->children.size(); ++i) {
            dumpTree(root->children[i].get());
        }
    }
}

void plazza::CmdParser::checkCmdIntegrity(plazza::ast_node *node) {

    if (node && node->type == ASTNodeType::CMD && node->value == "CMD") {
        if (node->children.size() != 3)
            throw plazza::CmdParserError("Wrong command format - usage : file COMMAND");
        if (node->children[0]->type != ASTNodeType::FILE)
            throw plazza::CmdParserError("Missing File to parse");
        if (node->children[1]->type != ASTNodeType::CMD)
            throw plazza::CmdParserError("Missing Command to parse the file");
        if (node->children[2]->type != ASTNodeType::END_CMD)
            throw plazza::CmdParserError("Command ill terminated");
    }
}

void plazza::CmdParser::checkIntegrity(plazza::ast_node *node) {
    if (node && node->type == ASTNodeType::ROOT) {
        for (size_t i = 0; i < node->children.size(); ++i) {
            checkCmdIntegrity(node->children[i].get());
        }
    }
}

size_t plazza::CmdParser::getNbCmd() {
    return nbCmd;
}