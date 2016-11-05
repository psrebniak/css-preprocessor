//
// Created by piotrek on 05.11.16.
//

#include "MediaEntry.hpp"

const std::string CSSP::AST::MediaEntry::toString() const {
    return "(" + this->name + ": " + this->value->toString() + ") ";
}
