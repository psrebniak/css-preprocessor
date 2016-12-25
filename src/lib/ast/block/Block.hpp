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

            /**
             * Constructor
             * @param selectorList
             * @param instructionList
             */
            Block(std::list<NodeListType*> *selectorList, NodeListType *instructionList)
                : Node("Block"),
                  selectorList(selectorList),
                  instructionList(instructionList) {}

            /**
             * @inherit
             * @param generator
             * @return
             */
            virtual const std::string generate(Generator *generator) const override;

            /**
             * @inherit
             * @return
             */
            virtual const std::string debugString() const override;

        protected:
            /**
             * List of selector entries
             */
            std::list<NodeListType*> *selectorList;

            /**
             * List of instructions inside current block
             */
            NodeListType *instructionList;

            /**
             * Helper method, do string concatenation from given list
             * @param list
             * @return
             */
            const std::string joinStringList(std::list<std::string> *list) const;

            /**
             * Helper method, remove trailing and leading spaces from given string
             * @param string
             * @return
             */
            const std::string trimString(std::string string) const;
        };
    }
}

#endif //CSSPREPROCESSOR_BLOCK_HPP
