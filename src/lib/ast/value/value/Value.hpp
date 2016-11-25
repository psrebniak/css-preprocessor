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
            Value(std::string nodeType)
                : Node(nodeType) {}

            virtual const std::string debugString() const override;

            virtual Value *setToken(CSSP::Token) override;

            virtual Value *getAsPrimitive(Generator *generator);
        };
    }
}

#endif //CSSPREPROCESSOR_VALUE_HPP
