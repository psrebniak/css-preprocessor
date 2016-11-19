//
// Created by piotrek on 18.10.16.
//

#include "lib/generator/Generator.hpp"
#include "VariableSetter.hpp"

const std::string CSSP::AST::VariableSetter::debugString() const {
    return "SET(" + this->name + ")\n";
}

const std::string CSSP::AST::VariableSetter::getName() const {
    return this->name;
}

CSSP::AST::Value *CSSP::AST::VariableSetter::getValue() const {
    return this->value;
}

const std::string CSSP::AST::VariableSetter::generate(CSSP::Generator *generator) const {
    generator->setVariable(this->getName(), this->getValue());
    return Node::generate(generator);
}
