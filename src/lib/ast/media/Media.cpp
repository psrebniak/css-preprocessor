//
// Created by piotrek on 05.11.16.
//

#include <sstream>
#include <iostream>
#include "Media.hpp"

const std::string CSSP::AST::Media::toString() const {
    std::stringstream stream;

    stream << "@media";

    for(int i = 0; i < this->mediaList->size(); i++) {
        stream
            << " " << (*this->mediaList)[i]->toString();
    }
    stream << " {" << std::endl;


    for(int i = 0; i < this->instructionList->size(); i++) {
        stream
            << (*this->instructionList)[i]->toString();
    }
    stream << "}" << std::endl;

    return stream.str();
}
