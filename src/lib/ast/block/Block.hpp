//
// Created by piotrek on 16.10.16.
//

#ifndef CSSPREPROCESSOR_BLOCK_HPP
#define CSSPREPROCESSOR_BLOCK_HPP

#include <vector>
#include "lib/types.hpp"
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Block : public Node {
        public:

            Block(NodeVectorType *selectorList, NodeVectorType *instructionList)
                : Node("Block"),
                  selectorList(selectorList),
                  instructionList(instructionList) {};


            virtual const std::string toString() const override;

        protected:
            NodeVectorType *selectorList;
            NodeVectorType *instructionList;
        };
    }
}

#endif //CSSPREPROCESSOR_BLOCK_HPP
