//
// Created by piotrek on 16.10.16.
//

#include "lib/generator/Generator.hpp"
#include <sstream>
#include <iterator>
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

const std::string CSSP::AST::Block::joinStringList(std::list<std::string> *list) const {
    if (list->size() == 0) {
        return std::string();
    } else if (list->size() == 1) {
        return list->back();
    }

    std::ostringstream imploded;
    const char *delimiter = ", ";
    std::copy(list->begin(), --list->end(), std::ostream_iterator<std::string>(imploded, delimiter));

    return imploded.str() + *(--list->end());
}

const std::string CSSP::AST::Block::trimString(std::string string) const {
    return string.erase(0, string.find_first_not_of(" \n\r\t"));
}

const std::string CSSP::AST::Block::generate(CSSP::Generator *generator) const {

    std::stringstream stream;
    std::list<std::string> *latestSelectorList = generator->getLatestBlockSelector();
    bool fakeParentObject = false;

    if (nullptr == latestSelectorList) {
        fakeParentObject = true;
        latestSelectorList = new std::list<std::string>();
        latestSelectorList->push_back(std::string());
    }

    std::list<std::string> *currentSelectorList = new std::list<std::string>();

    // for every item in comma separated selector list from parent selector list
    for (auto const parentSelector: *latestSelectorList) {
        // for every item in comma separated selector list from current selector list
        for (auto const currentSelector: *this->selectorList) {

            bool hasParentOperator = false;
            std::string currentSelectorString = std::string();

            // perform generation on every node from current selector
            for (auto const node: *currentSelector) {
                if (node->getToken().toString() == "&") {
                    hasParentOperator = true;
                    currentSelectorString =
                        currentSelectorString
                        + (node->getToken().isWhitespacePrefixed() ? " " : "")
                        + parentSelector;
                } else {
                    currentSelectorString += node->generate(generator);
                }
            }

            if (!hasParentOperator) {
                currentSelectorString = parentSelector + currentSelectorString;
            }
            currentSelectorList->push_back(currentSelectorString);
        }
    }

    generator->pushBlockSelector(currentSelectorList);

    std::string currentSelectorAsString = this->trimString(this->joinStringList(currentSelectorList));

    bool isCurrentSelectorWritten = false;
    for (auto const node: *this->instructionList) {
        if (!isCurrentSelectorWritten && node->getNodeType() == "Property") {
            stream << currentSelectorAsString << " {" << generator->getEol();
            isCurrentSelectorWritten = true;
        } else if (isCurrentSelectorWritten && node->getNodeType() != "Property") {
            stream << "}" << generator->getEol();
            isCurrentSelectorWritten = false;
        }

        stream
            << node->generate(generator);
    }
    if (isCurrentSelectorWritten) {
        stream << "}" << generator->getEol();
    }

    generator->popBlockSelector();
    if (fakeParentObject) {
        latestSelectorList->clear();
        delete latestSelectorList;
    }

    delete currentSelectorList;

    return stream.str();
}

CSSP::AST::Block::~Block() {
    while(!this->instructionList->empty()) {
        delete this->instructionList->front();
        this->instructionList->pop_front();
    }
    delete this->instructionList;

    while(!this->selectorList->empty()) {
        NodeListType *list = this->selectorList->front();
        while(!list->empty()) {
            delete list->front();
            list->pop_front();
        }
        delete list;
        this->selectorList->pop_front();
    }
    delete this->selectorList;
}
