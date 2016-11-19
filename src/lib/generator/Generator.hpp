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

#include "lib/ast/value/value/Value.hpp"
#include "lib/types.hpp"
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    class Generator {
    public:
        Generator(FileToTreeMapType *fileToTreeMap, std::string mainFile)
            : fileToTreeMap(*fileToTreeMap) {
            this->pushFile(mainFile);
        }

        long generateOutput(std::ostream &ostream);

        bool pushFile(const std::string filename);

        void registerError(const std::string description);

        bool setVariable(const std::string name, CSSP::AST::Value *value);

        const CSSP::AST::Value *getVariable(std::string name);

    protected:
        FileToTreeMapType fileToTreeMap;
        std::stack<std::pair<NodeVectorType::const_iterator, NodeVectorType *> > stack;

        NameToVariableMapType variableMap;
    };
}

#endif //CSSPREPROCESSOR_GENERATOR_HPP
