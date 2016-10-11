//
// Created by piotrek on 11.10.16.
//

#include "Modifier.hpp"

const std::string CSSP::AST::Modifier::toString() const {
    return "!" + this->modifier;
}
