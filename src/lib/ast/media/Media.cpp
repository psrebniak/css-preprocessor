//
// Created by piotrek on 05.11.16.
//

#include <sstream>
#include <iostream>
#include "Media.hpp"

const std::string CSSP::AST::Media::debugString() const {
    std::stringstream stream;

    stream << "@media";

    for (auto const node: *this->mediaList) {
        stream
            << " "
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

const std::string CSSP::AST::Media::generate(CSSP::Generator *generator) {
    std::stringstream stream;

    stream << "@media";

    for (auto const node: *this->mediaList) {
        stream
            << " "
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
