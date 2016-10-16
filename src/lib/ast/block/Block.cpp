//
// Created by piotrek on 16.10.16.
//

#include <sstream>
#include <iostream>
#include "Block.hpp"

const std::string CSSP::AST::Block::toString() const {
    std::stringstream stream;

    for(int i = 0; i < this->selectorList->size(); i++) {
        stream
            << (*this->selectorList)[i]->toString()
            << std::endl;
    }


    for(int i = 0; i < this->instructionList->size(); i++) {
        stream
            << (*this->instructionList)[i]->toString()
            << std::endl;
    }
    stream << "End of block" << std::endl;

    return stream.str();
}
