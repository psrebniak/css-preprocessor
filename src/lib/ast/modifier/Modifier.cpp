//
// Created by piotrek on 11.10.16.
//

#include "Modifier.hpp"

const std::string CSSP::AST::Modifier::debugString() const {
    if (this->modifier != "") {
        return " !" + this->modifier;
    }
    return "";
}
