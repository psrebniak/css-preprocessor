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
    while(!this->instructionList->empty()) {
        delete this->instructionList->front();
        this->instructionList->pop_front();
    }
    delete this->instructionList;

    while(!this->mediaList->empty()) {
        delete this->mediaList->front();
        this->mediaList->pop_front();
    }
    delete this->mediaList;
}
