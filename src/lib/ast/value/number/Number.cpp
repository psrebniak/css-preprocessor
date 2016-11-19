//
// Created by piotrek on 11.10.16.
//

#include <stdexcept>
#include <math.h>
#include "Number.hpp"

CSSP::AST::Number::Number(std::string number)
    : Value("Value/Number") {
    size_t offset = 0;
    try {
        this->number = std::stof(number, &offset);
    } catch (std::invalid_argument) {
        this->number = 0;
    }
    this->unit = number.substr(offset);
}

const std::string CSSP::AST::Number::debugString() const {
    return std::to_string(this->number) + "@" + this->unit;
}

const std::string CSSP::AST::Number::generate(CSSP::Generator *generator) const {
    return Number::floatToString(this->number) + this->unit;
}

const std::string CSSP::AST::Number::floatToString(float number) {
    // is integer?
    if (roundf(number) == number) {
        return std::to_string((int) number);
    }

    // remove trailing zeros from float
    std::string str = std::to_string(number);
    str.erase (str.find_last_not_of('0') + 1, std::string::npos);

    return str;
}
