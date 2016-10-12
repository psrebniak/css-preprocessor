//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_VARIABLE_HPP
#define CSSPREPROCESSOR_VARIABLE_HPP

#include <string>
#include "lib/ast/value/value/Value.hpp"

namespace CSSP {
    namespace AST {
        class Variable: public Value {
        public:
            Variable(std::string name)
                : name(name) {};

            virtual const std::string toString() const override;

        protected:
            std::string name;
            std::string nodeType = "Variable";
        };
    }
}


#endif //CSSPREPROCESSOR_VARIABLE_HPP
