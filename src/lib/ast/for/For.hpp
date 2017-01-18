//
// Created by piotrek on 27.12.16.
//

#ifndef CSSP_FOR_HPP
#define CSSP_FOR_HPP

#include <list>
#include "lib/types.hpp"
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    class Generator;

    namespace AST {
        class For : public Node {
        public:
            /**
             * Constructor
             * @param selectorList
             * @param instructionList
             */
            For(std::string name, Value *from, Value *to, NodeListType *instructionList)
            : Node("For"),
              name(name),
              from(from),
              to(to),
              instructionList(instructionList) {};

            ~For();

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
             * Variable name
             */
            std::string name;

            /**
             * Loop start index
             */
            Value *from = nullptr;

            /**
             * Loop end index
             */
            Value *to = nullptr;

            /**
             * List of instructions inside loop
             */
            NodeListType *instructionList = nullptr;
        };
    }
}


#endif //CSSP_FOR_HPP
