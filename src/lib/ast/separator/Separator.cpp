//
// Created by piotrek on 16.10.16.
//

#include "Separator.hpp"

const std::string CSSP::AST::Separator::debugString() const {
    return this->token.toString();
}

const std::string CSSP::AST::Separator::generate(CSSP::Generator *generator) {
    return this->debugString();
}
