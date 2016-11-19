//
// Created by piotrek on 16.10.16.
//
#include "lib/generator/Generator.hpp"
#include "Separator.hpp"

const std::string CSSP::AST::Separator::debugString() const {
    return this->token.toString();
}

const std::string CSSP::AST::Separator::generate(CSSP::Generator *generator) const {
    if (this->token.toString() == "&") {
        return (this->token.isWhitespacePrefixed() ? " " : std::string() ) + generator->getLatestBlockSelector();
    }

    return this->token.toString();
}
