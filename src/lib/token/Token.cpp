//
// Created by piotrek on 16.10.16.
//

#include "Token.hpp"

/**
 * get token string value
 * @return
 */
const std::string CSSP::Token::toString() const {
    return this->stringValue;
}

/**
 * true if before token was whitespace
 * @return
 */
const bool CSSP::Token::isWhitespacePrefixed() const {
    return this->whitespacePrefixed;
}

/**
 * return token int code (for tokens defined in parser.y file)
 * @return
 */
const int CSSP::Token::getTokenType() const {
    return this->tokenType;
}
