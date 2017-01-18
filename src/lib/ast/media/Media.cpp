//
// Created by piotrek on 05.11.16.
//

#include <sstream>
#include <iostream>
#include "Media.hpp"
#include "lib/generator/Generator.hpp"

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

const std::string CSSP::AST::Media::generate(CSSP::Generator *generator) const {
    std::stringstream stream;

    stream << "@media";

    for (auto const node: *this->mediaList) {
        stream
            << " "
            << node->generate(generator);
    }
    stream << " {" << generator->getEol();


    for (auto const node: *this->instructionList) {
        stream
            << node->generate(generator);
    }
    stream << "}" << generator->getEol();

    return stream.str();
}

CSSP::AST::Media::~Media() {
    for(const auto instruction : (*this->instructionList)) {
        if (instruction != nullptr) {
            delete instruction;
        }
    }
    delete this->instructionList;

    for(const auto media : (*this->mediaList)) {
        if (media != nullptr) {
            delete media;
        }
    }
    delete this->mediaList;
}
