//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_VARIABLE_HPP
#define CSSPREPROCESSOR_VARIABLE_HPP

#include <string>
#include "lib/ast/value/value/Value.hpp"

namespace CSSP {
    namespace AST {
        class Variable : public Value {
        public:
            /**
             * Constructor
             * @param name
             */
            Variable(std::string name)
                : Value("Value/Variable"),
                  name(name) {};

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

            /**
             * Returns variable value
             * @param generator
             * @return
             */
            virtual Value *getAsPrimitive(Generator *generator) override;

        protected:
            /**
             * Variable name
             */
            std::string name;
        };
    }
}


#endif //CSSPREPROCESSOR_VARIABLE_HPP
