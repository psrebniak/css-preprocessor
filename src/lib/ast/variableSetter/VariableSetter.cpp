//
// Created by piotrek on 18.10.16.
//

#include "VariableSetter.hpp"

const std::string CSSP::AST::VariableSetter::toString() const {
    return "SET(" + this->name + ")\n";
}

const std::string CSSP::AST::VariableSetter::getName() const {
    return this->name;
}

const CSSP::AST::Value *CSSP::AST::VariableSetter::getValue() const {
    return this->value;
}
