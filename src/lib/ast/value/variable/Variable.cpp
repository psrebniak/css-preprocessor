//
// Created by piotrek on 11.10.16.
//

#include "Variable.hpp"

const std::string CSSP::AST::Variable::debugString() const {
    return "#{" + this->name + "}";
}
