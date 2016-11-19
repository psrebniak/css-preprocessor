//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_NUMBER_HPP
#define CSSPREPROCESSOR_NUMBER_HPP

#include "lib/ast/value/value/Value.hpp"

namespace CSSP {
    namespace AST {
        class Number : public Value {
        public:
            Number(std::string);

            virtual const std::string debugString() const override;

        protected:
            float number;
            std::string unit;
        };
    }
}

#endif //CSSPREPROCESSOR_NUMBER_HPP
