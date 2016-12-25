//
// Created by piotrek on 12.10.16.
//

#ifndef CSSPREPROCESSOR_CALCULATION_HPP
#define CSSPREPROCESSOR_CALCULATION_HPP


#include "lib/ast/value/value/Value.hpp"

namespace CSSP {
    class Generator;

    namespace AST {
        class Calculation : public Value {
        public:
            /**
             * Constructor
             * @param first
             * @param second
             * @param operation
             */
            Calculation(Value *first, Value *second, int operation)
                : Value("Value/Calculation"),
                  first(first),
                  second(second),
                  operation(operation) {};

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

        protected:
            /**
             * first operand
             */
            Value *first;

            /**
             * second operand
             */
            Value *second;

            /**
             * operation code (bison token code)
             */
            int operation;
        };
    }
}

#endif //CSSPREPROCESSOR_CALCULATION_HPP
