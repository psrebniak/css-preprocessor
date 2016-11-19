//
// Created by piotrek on 11.10.16.
//

#include "String.hpp"

const std::string CSSP::AST::String::debugString() const {
    return this->value;
}

const std::string CSSP::AST::String::generate(CSSP::Generator *generator) {
    return this->debugString();
}
