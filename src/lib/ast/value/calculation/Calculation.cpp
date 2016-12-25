//
// Created by piotrek on 12.10.16.
//

#include "lib/ast/value/string/String.hpp"
#include "lib/ast/value/number/Number.hpp"
#include "Calculation.hpp"

#include "lib/generator/Generator.hpp"
#include "generated/parser.hpp"

using token = CSSP::Parser::token;

const std::string CSSP::AST::Calculation::debugString() const {
    return std::string("Not implemented yet");
}

const std::string CSSP::AST::Calculation::generate(CSSP::Generator *generator) const {
    // compute numbers
    CSSP::AST::Value *first = this->first->getAsPrimitive(generator);
    CSSP::AST::Value *second = this->second->getAsPrimitive(generator);

    bool freeFirstElement = false;
    bool freeSecondElement = false;

    if (first->getNodeType() == "Value/Calculation") {
        freeFirstElement = true;
        std::string v1 = first->generate(generator);
        try {
            std::stoi(v1);
            first = new CSSP::AST::Number(v1);
        } catch (std::invalid_argument) {
            first = new CSSP::AST::String(v1);
        }
    }
    if (second->getNodeType() == "Value/Calculation") {
        freeSecondElement = true;
        std::string v2 = second->generate(generator);
        try {
            std::stoi(v2);
            second = new CSSP::AST::Number(v2);
        } catch (std::invalid_argument) {
            second = new CSSP::AST::String(v2);
        }
    }

    if (first->getNodeType() == "Value/Number" && second->getNodeType() == "Value/Number") {
        CSSP::AST::Number *firstNumber = (CSSP::AST::Number *) first;
        CSSP::AST::Number *secondNumber = (CSSP::AST::Number *) second;

        if (firstNumber->getUnit() != std::string() && secondNumber->getUnit() != std::string() &&
            firstNumber->getUnit() != secondNumber->getUnit()) {
            generator->registerError("Performing calculations on numbers with different units");
        }
        std::string unit = firstNumber->getUnit();
        if (unit == std::string()) {
            unit = secondNumber->getUnit();
        }

        float value = 0;

        switch (this->operation) {
            case token::PLUS: {
                value = firstNumber->getValue() + secondNumber->getValue();
                break;
            }
            case token::MINUS: {
                value = firstNumber->getValue() - secondNumber->getValue();
                break;
            }
            case token::ASTERISK: {
                value = firstNumber->getValue() * secondNumber->getValue();
                break;
            }
            case token::DIVIDE: {
                if (secondNumber->getValue() == 0) {
                    generator->registerError("Cannot divide by 0");
                    break;
                }
                value = firstNumber->getValue() / secondNumber->getValue();
                break;
            }
            default: {
                generator->registerError("Unknown operation in calculation");
            }
        }

        if (freeFirstElement) {
            delete first;
        }
        if (freeSecondElement) {
            delete second;
        }

        return Number::floatToString(value) + unit;
    }

    if (this->operation != token::PLUS) {
        generator->registerError(
            "Only PLUS operator is allowed on non-number values; Got "
            + first->getNodeType()
            + " and "
            + second->getNodeType()
        );

        if (freeFirstElement) {
            delete first;
        }
        if (freeSecondElement) {
            delete second;
        }

        return "";
    }
    std::string ret = first->generate(generator) + second->generate(generator);
    if (freeFirstElement) {
        delete first;
    }
    if (freeSecondElement) {
        delete second;
    }

    return ret;
}
