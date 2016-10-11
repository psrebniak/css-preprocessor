//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_MODIFIER_HPP
#define CSSPREPROCESSOR_MODIFIER_HPP

#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Modifier : public Node {
        public:
            Modifier() = default;

            Modifier(std::string modifier)
                : modifier(modifier) {};

            virtual const std::string toString() const override;

        protected:
            std::string modifier;

            std::string nodeType = "Modifier";
        };
    }
}


#endif //CSSPREPROCESSOR_MODIFIER_HPP
