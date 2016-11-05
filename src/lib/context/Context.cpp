//
// Created by piotrek on 05.11.16.
//

#include "Context.hpp"
#include <utility>

bool CSSP::Context::setVariable(CSSP::AST::VariableSetter *variable) {
    this->variables.insert(std::pair<std::string, const AST::Value*>(variable->getName(), variable->getValue()));
}

unsigned int CSSP::Context::generateCode(std::stringstream output, std::vector<AST::Node *> *instructionList) {
    
}
