//
// Created by piotrek on 16.10.16.
//

#include <sstream>
#include "Selector.hpp"

const std::string CSSP::AST::Selector::toString() const {
    std::stringstream stream;
    if (this->getToken().isWhitespacePrefixed()) {
        stream << " ";
    }
    stream << this->getSelectorPrefix() << this->name;
    if (this->value != NULL) {
        stream << "=" << value->toString();
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
