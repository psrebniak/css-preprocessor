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
            Variable(std::string name)
                : Value("Value/Variable"),
                  name(name) {};

            virtual const std::string debugString() const override;

        protected:
            std::string name;
        };
    }
}


#endif //CSSPREPROCESSOR_VARIABLE_HPP
