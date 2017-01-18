//
// Created by piotrek on 05.11.16.
//

#include "MediaEntry.hpp"

const std::string CSSP::AST::MediaEntry::debugString() const {
    return "(" + this->name + ": " + this->value->debugString() + ") ";
}

const std::string CSSP::AST::MediaEntry::generate(CSSP::Generator *generator) const {
    return "(" + this->name + ": " + this->value->generate(generator) + ") ";
}

CSSP::AST::MediaEntry::~MediaEntry() {
    if (this->value != nullptr) {
        delete this->value;
    }
}
