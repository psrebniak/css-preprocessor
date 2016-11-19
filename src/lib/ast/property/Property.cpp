//
// Created by piotrek on 11.10.16.
//

#include <sstream>
#include "Property.hpp"

const std::string CSSP::AST::Property::debugString() const {

    std::stringstream stream;
    stream
        << this->name->debugString()
        << ":";

    for (auto const &value: *this->valueList) {
        if (value->getToken().isWhitespacePrefixed()) {
            stream << " ";
        }
        stream << value->debugString();
    }
    stream << this->modifier->debugString() << ";" << std::endl;

    return stream.str();
}

const std::string CSSP::AST::Property::generate(CSSP::Generator *generator) const {
    std::stringstream stream;
    stream
        << this->name->generate(generator)
        << ":";

    for (auto const &value: *this->valueList) {
        if (value->getToken().isWhitespacePrefixed()) {
            stream << " ";
        }
        stream << value->generate(generator);
    }
    stream << this->modifier->generate(generator) << ";" << std::endl;

    return stream.str();
}

