//
// Created by piotrek on 11.10.16.
//

#include "Number.hpp"

CSSP::AST::Number::Number(std::string number) {
    this->number = std::stof(number);
    std::string partAsString = std::to_string(this->number);
    this->unit = unit.substr(partAsString.length());
}

CSSP::AST::Number::Number(std::string number, std::string unit) {
    int part = std::stoi(unit);
    this->number = std::stof(number + "." + unit);
    std::string partAsString = std::to_string(part);
    this->unit = unit.substr(partAsString.length());
}

const std::string CSSP::AST::Number::toString() const {
    return std::to_string(this->number) + "@" + this->unit;
}
