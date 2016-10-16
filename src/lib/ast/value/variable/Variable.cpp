//
// Created by piotrek on 11.10.16.
//

#include "Variable.hpp"

const std::string CSSP::AST::Variable::toString() const {
    return "#{" + this->name + "}";
}
