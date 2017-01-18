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
            /**
             * Constructor
             */
            Modifier()
                : Node("Modifier") {}

            /**
             * Constructor
             * @param modifier
             */
            Modifier(std::string modifier)
                : Node("Modifier"),
                  modifier(modifier) {}

            virtual ~Modifier() = default;

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
             * modifier real value or empty string if modifier is not exist
             */
            std::string modifier;
        };
    }
}


#endif //CSSPREPROCESSOR_MODIFIER_HPP
