//
// Created by piotrek on 14.11.16.
//

#ifndef CSSPREPROCESSOR_GENERATOR_HPP
#define CSSPREPROCESSOR_GENERATOR_HPP

#include <utility>
#include <map>
#include <list>
#include <stack>
#include <fstream>
#include <src/lib/logger/Logger.hpp>

#include "lib/ast/value/value/Value.hpp"
#include "lib/types.hpp"
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    class Generator {
    public:
        Generator(FileToTreeMapType *fileToTreeMap, std::string mainFile, bool minify = false)
            : fileToTreeMap(*fileToTreeMap),
            error(std::cerr, Logger::colorRed),
            minify(minify) {
            this->pushFile(mainFile);
        }

        int generateOutput(std::ostream &ostream);

        bool pushFile(const std::string filename);

        void registerError(const std::string description);

        bool setVariable(const std::string name, CSSP::AST::Value *value);

        const CSSP::AST::Value *getVariable(std::string name);
        void pushBlockSelector(std::list<std::string>*);
        void popBlockSelector();
        std::list<std::string> *getLatestBlockSelector();

        const std::string getIndent() const;
        const std::string getEol() const;
        const bool isMinified() const;
        Logger error;
    protected:
        FileToTreeMapType fileToTreeMap;
        std::stack<std::pair<NodeListType::const_iterator, NodeListType *> > stack;
        std::stack<std::list<std::string>*> blockSelectors;

        NameToVariableMapType variableMap;
        bool minify;
        const int MAX_STACK_SIZE = 16;
    };
}

#endif //CSSPREPROCESSOR_GENERATOR_HPP
