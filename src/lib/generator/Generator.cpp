#include <src/lib/ast/import/Import.hpp>
#include <iostream>
#include "Generator.hpp"

int CSSP::Generator::generateOutput(std::ostream &ostream) {

    while (!this->stack.empty()) {
        std::pair<NodeListType::const_iterator, NodeListType *> *top = &this->stack.top();

        NodeListType::const_iterator iterator = top->first;
        NodeListType *nodes = top->second;

        if (iterator == nodes->end()) {
            this->stack.pop();
            continue;
        }

        ostream << (*iterator)->generate(this);
        ++top->first;
    }
    return 0;
}

bool CSSP::Generator::pushFile(std::string filename) {
    if (this->stack.size() >= this->MAX_STACK_SIZE) {
        this->registerError("Cannot include file " + filename + "; Stack size exceed");
        return false;
    }
    FileToTreeMapType::const_iterator position = this->fileToTreeMap.find(filename);
    if (position != this->fileToTreeMap.end()) {
        this->stack.push(std::pair<NodeListType::const_iterator, NodeListType *>(
            position->second->begin(),
            position->second
        ));
        return true;
    }
    return false;
}

bool CSSP::Generator::setVariable(const std::string name, CSSP::AST::Value *value) {
    NameToVariableMapType::iterator iterator = this->variableMap.find(name);
    if (iterator == this->variableMap.end()) {
        this->variableMap.insert(NameToVariablePairType(
            name,
            value
        ));
        return true;
    }
    iterator->second = value;
    return true;
}

const CSSP::AST::Value *CSSP::Generator::getVariable(const std::string name) {
    NameToVariableMapType::const_iterator iterator = this->variableMap.find(name);
    if (iterator == this->variableMap.end()) {
        return NULL;
    }
    return iterator->second;
}

void CSSP::Generator::registerError(std::string description) {
    this->error << description << this->error.end() << std::endl;
}

void CSSP::Generator::pushBlockSelector(std::list<std::string> *selector) {
    this->blockSelectors.push(selector);
}

void CSSP::Generator::popBlockSelector() {
    if (this->blockSelectors.size() == 0) {
        this->registerError("Cannot pop block selector from empty stack");
        return;
    }
    this->blockSelectors.pop();
}

std::list<std::string> *CSSP::Generator::getLatestBlockSelector() {
    if (this->blockSelectors.size() == 0) {
        return NULL;
    }
    return this->blockSelectors.top();
}

const std::string CSSP::Generator::getIndent() const {
    return (this->minify) ? std::string() : std::string("    ");
}

const std::string CSSP::Generator::getEol() const {
    return (this->minify) ? std::string() : std::string("\n");
}

const bool CSSP::Generator::isMinified() const {
    return this->minify;
}
