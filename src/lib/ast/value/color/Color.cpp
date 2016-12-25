//
// Created by piotrek on 11.10.16.
//

#include <list>
#include <sstream>
#include <iterator>
#include "Color.hpp"

const std::string CSSP::AST::Color::debugString() const {
    return "#" + this->value;
}

const std::string CSSP::AST::Color::generate(CSSP::Generator *generator) const {
    return this->debugString();
}
