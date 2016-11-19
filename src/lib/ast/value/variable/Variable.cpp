//
// Created by piotrek on 11.10.16.
//

#include "lib/generator/Generator.hpp"
#include "Variable.hpp"

const std::string CSSP::AST::Variable::debugString() const {
    return "#{" + this->name + "}";
}

const std::string CSSP::AST::Variable::generate(CSSP::Generator *generator) {
    const CSSP::AST::Value *constValue = generator->getVariable(this->name);
    if (constValue != nullptr) {
        ///@todo do it better
        CSSP::AST::Value *value = const_cast<CSSP::AST::Value*>(constValue);
        return value->generate(generator);
    }
    generator->registerError("Cannot find variable: " + this->name);
    return Node::generate(generator);
}
