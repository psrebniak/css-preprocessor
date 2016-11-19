//
// Created by piotrek on 16.10.16.
//

#include <sstream>
#include "Block.hpp"

const std::string CSSP::AST::Block::debugString() const {
    std::stringstream stream;

    for (auto const node: *this->selectorList) {
        stream
            << node->debugString();
    }
    stream << " {" << std::endl;


    for (auto const node: *this->instructionList) {
        stream
            << node->debugString();
    }
    stream << "}" << std::endl;

    return stream.str();
}

const std::string CSSP::AST::Block::generate(CSSP::Generator *generator) const {
    std::stringstream stream;

    for (auto const node: *this->selectorList) {
        stream
            << node->generate(generator);
    }
    stream << " {" << std::endl;


    for (auto const node: *this->instructionList) {
        stream
            << node->generate(generator);
    }
    stream << "}" << std::endl;

    return stream.str();
}

