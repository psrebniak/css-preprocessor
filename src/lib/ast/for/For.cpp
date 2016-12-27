//
// Created by piotrek on 27.12.16.
//

#include <sstream>
#include "lib/ast/value/number/Number.hpp"
#include "lib/generator/Generator.hpp"

#include "For.hpp"

const std::string CSSP::AST::For::generate(CSSP::Generator *generator) const {
    const Value *var = generator->getVariable(this->name);

    Value *from = this->from->getAsPrimitive(generator);
    Value *to = this->to->getAsPrimitive(generator);

    if (from->getNodeType() != "Value/Number" || to->getNodeType() != "Value/Number") {
        generator->registerError("Invalid loop range detected");
        return "";
    }
    int fromInt = (int) ((Number*) from)->getValue();
    int toInt = (int) ((Number*) to)->getValue();
    int jump = (fromInt < toInt) ? 1 : -1;

    std::stringstream stream;

    int index  = fromInt;
    while(true) {
        Number indexValue = Number(std::to_string(index));
        generator->setVariable(this->name, &indexValue);
        for(auto const instruction: *this->instructionList) {
            stream << instruction->generate(generator);
        }
        if (index == toInt) {
            break;
        }
        index += jump;
    }
    generator->unsetVariable(this->name);

    if (var != nullptr) {
        generator->setVariable(this->name, const_cast<Value*>(var));
    }

    return stream.str();
}

const std::string CSSP::AST::For::debugString() const {
    std::stringstream stream;
    stream << "For loop " << std::endl;
    stream << "From: " << this->from->debugString() << std::endl;
    stream << "To: " << this->to->debugString() << std::endl;

    for(auto const instruction: *this->instructionList) {
        stream << instruction->debugString();
    }
    stream << "END FOR" << std::endl;
    return stream.str();
}
