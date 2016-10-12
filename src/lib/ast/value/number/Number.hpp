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

            Number(std::string, std::string unit);

            virtual const std::string toString() const override;

        protected:
            float number;
            std::string unit;

            std::string nodeType = "Color";
        };
    }
}

#endif //CSSPREPROCESSOR_NUMBER_HPP
