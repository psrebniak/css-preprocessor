//
// Created by piotrek on 14.11.16.
//

#ifndef CSSPREPROCESSOR_GENERATOR_HPP
#define CSSPREPROCESSOR_GENERATOR_HPP

#include <utility>
#include <map>
#include <vector>
#include <stack>
#include <fstream>
#include <src/lib/logger/Logger.hpp>

#include "lib/ast/value/value/Value.hpp"
#include "lib/types.hpp"
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    class Generator {
    public:
        Generator(FileToTreeMapType *fileToTreeMap, std::string mainFile)
            : fileToTreeMap(*fileToTreeMap),
            error(std::cerr, Logger::colorRed){
            this->pushFile(mainFile);
        }

        int generateOutput(std::ostream &ostream);

        bool pushFile(const std::string filename);

        void registerError(const std::string description);

        bool setVariable(const std::string name, CSSP::AST::Value *value);

        const CSSP::AST::Value *getVariable(std::string name);
        void pushBlockSelector(std::vector<std::string>*);
        void popBlockSelector();
        std::vector<std::string> *getLatestBlockSelector();

        Logger error;
    protected:
        FileToTreeMapType fileToTreeMap;
        std::stack<std::pair<NodeVectorType::const_iterator, NodeVectorType *> > stack;
        std::stack<std::vector<std::string>*> blockSelectors;

        NameToVariableMapType variableMap;


    };
}

#endif //CSSPREPROCESSOR_GENERATOR_HPP
