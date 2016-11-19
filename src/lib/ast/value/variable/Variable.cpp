//
// Created by piotrek on 11.10.16.
//

#include "lib/generator/Generator.hpp"
#include "Variable.hpp"

const std::string CSSP::AST::Variable::debugString() const {
    return "#{" + this->name + "}";
}

const std::string CSSP::AST::Variable::generate(CSSP::Generator *generator) const {
    const CSSP::AST::Value *value = generator->getVariable(this->name);
    if (value != nullptr) {
        return value->generate(generator);
    }
    generator->registerError("Cannot find variable: " + this->name);
    return Node::generate(generator);
}

CSSP::AST::Value *CSSP::AST::Variable::getAsPrimitive(Generator *generator) {
    CSSP::AST::Value *value = const_cast<CSSP::AST::Value *>(generator->getVariable(this->name));

    if (value != nullptr) {
        return value->getAsPrimitive(generator);
    }
    return new Value("Value/Unknown");
}
