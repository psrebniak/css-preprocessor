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
#include <iostream>

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

    protected:
        FileToTreeMapType fileToTreeMap;
        std::stack<std::pair<NodeVectorType::const_iterator, NodeVectorType *>> stack;

        bool pushFile(std::string filename);
    };
}

#endif //CSSPREPROCESSOR_GENERATOR_HPP
