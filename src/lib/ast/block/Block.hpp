//
// Created by piotrek on 16.10.16.
//

#ifndef CSSPREPROCESSOR_BLOCK_HPP
#define CSSPREPROCESSOR_BLOCK_HPP

#include <vector>
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Block : public Node {
        public:

            Block(std::vector<Node*>* selectorList, std::vector<Node*>* instructionList)
                : selectorList(selectorList),
                  instructionList(instructionList) {};


            virtual const std::string toString() const override;

        protected:
            std::vector<Node*>* selectorList;
            std::vector<Node*>* instructionList;

            std::string nodeType = "Block";
        };
    }
}

#endif //CSSPREPROCESSOR_BLOCK_HPP
