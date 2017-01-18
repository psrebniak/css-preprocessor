//
// Created by piotrek on 11.10.16.
//

#include <sstream>
#include "Property.hpp"
#include "lib/generator/Generator.hpp"

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
        << generator->getIndent()
        << this->name->generate(generator)
        << ":";

    for (auto const &value: *this->valueList) {
        if (value->getToken().isWhitespacePrefixed()) {
            stream << " ";
        }
        stream << value->generate(generator);
    }
    stream << this->modifier->generate(generator) << ";" << generator->getEol();

    return stream.str();
}

CSSP::AST::Property::~Property() {
    for(const auto value : (*this->valueList)) {
        if (value != nullptr) {
            delete value;
        }
    }
    delete this->valueList;

    if (this->modifier != nullptr) {
        delete this->modifier;
    }

    if (this->name != nullptr) {
        delete this->name;
    }
}
