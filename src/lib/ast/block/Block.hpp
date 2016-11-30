//
// Created by piotrek on 16.10.16.
//

#ifndef CSSPREPROCESSOR_BLOCK_HPP
#define CSSPREPROCESSOR_BLOCK_HPP

#include <list>
#include "lib/types.hpp"
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Block : public Node {
        public:

            Block(std::list<NodeListType*> *selectorList, NodeListType *instructionList)
                : Node("Block"),
                  selectorList(selectorList),
                  instructionList(instructionList) {}

            virtual const std::string generate(Generator *generator) const override;


            virtual const std::string debugString() const override;

        protected:
            std::list<NodeListType*> *selectorList;
            NodeListType *instructionList;

            const std::string joinStringList(std::list<std::string> *list) const;
            const std::string trimString(std::string string) const;
        };
    }
}

#endif //CSSPREPROCESSOR_BLOCK_HPP
