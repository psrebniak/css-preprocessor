#include <utility>
#include "Context.hpp"

bool CSSP::Context::setVariable(CSSP::AST::VariableSetter *variable) {
    return this
        ->variables
        .insert(
            std::pair
                <std::string, const AST::Value*>
                (variable->getName(), variable->getValue())
        ).second;
}

unsigned int CSSP::Context::generateCode(std::stringstream output, std::vector<AST::Node *> *instructionList) {

}
