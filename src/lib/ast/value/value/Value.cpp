//
// Created by piotrek on 11.10.16.
//

#include "Value.hpp"

const std::string CSSP::AST::Value::debugString() const {
    return nullptr;
}

CSSP::AST::Value *CSSP::AST::Value::setToken(CSSP::Token token) {
    this->token = token;

    return this;
}
