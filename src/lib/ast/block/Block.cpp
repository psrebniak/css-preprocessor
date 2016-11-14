//
// Created by piotrek on 16.10.16.
//

#include <sstream>
#include "Block.hpp"

const std::string CSSP::AST::Block::toString() const {
    std::stringstream stream;

    for (auto const node: *this->selectorList) {
        stream
            << node->toString();
    }
    stream << " {" << std::endl;


    for (auto const node: *this->instructionList) {
        stream
            << node->toString();
    }
    stream << "}" << std::endl;

    return stream.str();
}
