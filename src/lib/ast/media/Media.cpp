//
// Created by piotrek on 05.11.16.
//

#include <sstream>
#include <iostream>
#include "Media.hpp"

const std::string CSSP::AST::Media::toString() const {
    std::stringstream stream;

    stream << "@media";

    for (auto const node: *this->mediaList) {
        stream
            << " "
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
