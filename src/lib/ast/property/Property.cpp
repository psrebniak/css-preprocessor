//
// Created by piotrek on 11.10.16.
//

#include <sstream>
#include "Property.hpp"

const std::string CSSP::AST::Property::toString() const {

    std::stringstream stream;
    stream
        << this->name->toString()
        << ":";

    for (auto const &value: *this->valueList) {
        if (value->getToken().isWhitespacePrefixed()) {
            stream << " ";
        }
        stream << value->toString();
    }
    stream << this->modifier->toString() << ";" << std::endl;

    return stream.str();
}

