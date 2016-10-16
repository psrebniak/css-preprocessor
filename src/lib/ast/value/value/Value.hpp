//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_VALUE_HPP
#define CSSPREPROCESSOR_VALUE_HPP

#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Value : public Node {
        public:
            virtual const std::string toString() const override;

            virtual Value* setToken(CSSP::Token);

        protected:
            std::string nodeType = "Value";
        };
    }
}

#endif //CSSPREPROCESSOR_VALUE_HPP
