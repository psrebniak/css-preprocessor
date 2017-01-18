//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_VALUE_HPP
#define CSSPREPROCESSOR_VALUE_HPP

#include "lib/ast/node/Node.hpp"

namespace CSSP {
    class Generator;

    namespace AST {
        class Value : public Node {
        public:
            /**
             * Constructor
             * @param nodeType
             */
            Value(std::string nodeType)
                : Node(nodeType) {}

            virtual ~Value() = default;

            /**
             * @inherit
             * @return
             */
            virtual const std::string debugString() const override;

            /**
             * @inherit
             * @return
             */
            virtual Value *setToken(CSSP::Token) override;

            /**
             * Return value as primitive (eg. variable value instead of variable)
             * @param generator
             * @return
             */
            virtual Value *getAsPrimitive(Generator *generator);
        };
    }
}

#endif //CSSPREPROCESSOR_VALUE_HPP
