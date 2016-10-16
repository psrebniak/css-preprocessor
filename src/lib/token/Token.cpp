//
// Created by piotrek on 16.10.16.
//

#include "Token.hpp"

const std::string CSSP::Token::toString() const {
    return this->stringValue;
}

const bool CSSP::Token::isWhitespacePrefixed() const {
    return this->whitespacePrefixed;
}

const int CSSP::Token::getTokenType() const {
    return this->tokenType;
}
