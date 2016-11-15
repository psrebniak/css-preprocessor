//
// Created by piotrek on 12.10.16.
//

#ifndef CSSPREPROCESSOR_CALCULATION_HPP
#define CSSPREPROCESSOR_CALCULATION_HPP


#include "lib/ast/value/value/Value.hpp"

namespace CSSP {
    namespace AST {
        class Calculation : public Value {
        public:
            Calculation(Value *first, Value *second, int operation)
                : Value("Value/Calculation"),
                  first(first),
                  second(second),
                  operation(operation) {};

            virtual const std::string toString() const override;

        protected:
            Value *first;
            Value *second;
            int operation;
        };
    }
}

#endif //CSSPREPROCESSOR_CALCULATION_HPP
