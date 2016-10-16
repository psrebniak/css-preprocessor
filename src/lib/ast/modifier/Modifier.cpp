//
// Created by piotrek on 11.10.16.
//

#include "Modifier.hpp"

const std::string CSSP::AST::Modifier::toString() const {
    if (this->modifier != "") {
        return " !" + this->modifier;
    }
    return "";
}
