//
// Created by piotrek on 26.01.17.
//

#include <sstream>
#include "FunctionCall.hpp"

const std::string CSSP::AST::FunctionCall::generate(Generator *generator) const {
    std::stringstream stream;

    stream << this->functionName << "(";
    for(const auto value : (*this->valueList)) {
        stream << value->generate(generator);
    }
    stream << ")";

    return stream.str();
}

CSSP::AST::FunctionCall::~FunctionCall() {
    while(!this->valueList->empty()) {
        delete this->valueList->front();
        this->valueList->pop_front();
    }
    delete this->valueList;
}
