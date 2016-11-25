//
// Created by piotrek on 16.10.16.
//

#include "lib/generator/Generator.hpp"
#include <sstream>
#include "Block.hpp"

const std::string CSSP::AST::Block::debugString() const {
    std::stringstream stream;
/*
    for (auto const node: *this->selectorList) {
        stream
            << node->debugString();
    }
    stream << " {" << std::endl;


    for (auto const node: *this->instructionList) {
        stream
            << node->debugString();
    }
    stream << "}" << std::endl;
*/
    return stream.str();
}

const std::string CSSP::AST::Block::generate(CSSP::Generator *generator) const {
    std::stringstream stream;
    std::vector<std::string> *latestSelectorList = generator->getLatestBlockSelector();
    std::vector<std::string> *currentSelectorList = new std::vector<std::string>();

    for (auto const selector: *latestSelectorList) {
        bool hasParentSelector = false;
        std::string currentSelector = std::string();
        for(auto const node: selector) {

        }
    }

    /*
    std::string latestSelector = generator->getLatestBlockSelector();

    std::string currentSelector = "";
    bool hasParentOperator = false;

    for (auto const node: *this->selectorList) {
        stream
            << node->generate(generator);

        if (node->getToken().toString() == "&") {
            hasParentOperator = true;
        }
    }

    if (!hasParentOperator) {
        currentSelector = latestSelector;
    }
    currentSelector += stream.str();
    stream << std::endl;
    stream.str(std::string());
    generator->pushBlockSelector(currentSelector);

    bool isCurrentSelectorWritten = false;
    for (auto const node: *this->instructionList) {
        if (!isCurrentSelectorWritten && node->getNodeType() == "Property") {
            stream << currentSelector << " {" << std::endl;
            isCurrentSelectorWritten = true;
        } else if (isCurrentSelectorWritten && node->getNodeType() != "Property") {
            stream << "\n } " << std::endl;
        }

        stream
            << node->generate(generator);
    }
    if (isCurrentSelectorWritten) {
        stream << "}" << std::endl;
    }

    generator->popBlockSelector();
*/
    return stream.str();

}
