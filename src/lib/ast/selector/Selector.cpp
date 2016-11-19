//
// Created by piotrek on 16.10.16.
//

#include <sstream>
#include "Selector.hpp"

const std::string CSSP::AST::Selector::debugString() const {
    std::stringstream stream;
    if (this->getToken().isWhitespacePrefixed()) {
        stream << " ";
    }
    stream << this->getSelectorPrefix() << this->name;
    if (this->value != nullptr) {
        stream << "=" << value->debugString();
    }
    if (this->type == SelectorType::ATTRIBUTE || this->type == SelectorType::ATTRIBUTE_VALUE) {
        stream << "]";
    };
    return stream.str();
}

const std::string CSSP::AST::Selector::generate(CSSP::Generator *generator) const {
    std::stringstream stream;
    if (this->getToken().isWhitespacePrefixed()) {
        stream << " ";
    }
    stream << this->getSelectorPrefix() << this->name;
    if (this->value != nullptr) {
        stream << "=" << value->generate(generator);
    }
    if (this->type == SelectorType::ATTRIBUTE || this->type == SelectorType::ATTRIBUTE_VALUE) {
        stream << "]";
    };
    return stream.str();
}

std::string CSSP::AST::Selector::getSelectorType() const {
    return (this->selectorToStringMap.at(this->type)).first;
}

std::string CSSP::AST::Selector::getSelectorPrefix() const {
    return (this->selectorToStringMap.at(this->type)).second;
}
