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
            Modifier()
                : Node("Modifier") {}

            Modifier(std::string modifier)
                : Node("Modifier"),
                  modifier(modifier) {}

            virtual const std::string generate(Generator *generator) override;;

            virtual const std::string debugString() const override;

        protected:
            std::string modifier;
        };
    }
}


#endif //CSSPREPROCESSOR_MODIFIER_HPP
