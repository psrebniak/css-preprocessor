//
// Created by piotrek on 16.10.16.
//

#ifndef CSSPREPROCESSOR_SEPARATOR_HPP
#define CSSPREPROCESSOR_SEPARATOR_HPP

#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Separator : public Node {
        public:
            /**
             * Constructor
             */
            Separator()
                : Node("Separator") {};

            /**
             * @inherit
             * @return
             */
            virtual const std::string debugString() const override;

            /**
             * @inherit
             * @param generator
             * @return
             */
            virtual const std::string generate(Generator *generator) const override;
        };
    }
}

#endif //CSSPREPROCESSOR_SEPARATOR_HPP
