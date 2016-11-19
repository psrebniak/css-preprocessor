//
// Created by piotrek on 11.10.16.
//

#include "Value.hpp"

const std::string CSSP::AST::Value::debugString() const {
    return std::string();
}

CSSP::AST::Value *CSSP::AST::Value::setToken(CSSP::Token token) {
    this->token = token;

    return this;
}

CSSP::AST::Value *CSSP::AST::Value::getAsPrimitive(Generator *generator) {
    return this;
}
