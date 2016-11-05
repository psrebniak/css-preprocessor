//
// Created by piotrek on 11.10.16.
//

#include "Node.hpp"

const std::string &CSSP::AST::Node::getNodeType() const {
    return nodeType;
}

CSSP::AST::Node *CSSP::AST::Node::setToken(CSSP::Token token) {
    this->token = token;

    return this;
}

CSSP::Token CSSP::AST::Node::getToken() const {
    return this->token;
}
