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

