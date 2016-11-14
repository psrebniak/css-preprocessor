//
// Created by piotrek on 18.10.16.
//

#ifndef CSSPREPROCESSOR_VARIABLESETTER_HPP
#define CSSPREPROCESSOR_VARIABLESETTER_HPP

#include "lib/ast/node/Node.hpp"
#include "lib/ast/value/value/Value.hpp"

namespace CSSP {
    namespace AST {
        class VariableSetter : public Node {
        public:
            VariableSetter(std::string name, Value *value)
                : name(name),
                  value(value) {};

            virtual const std::string toString() const override;

            const std::string getName() const;

            const Value *getValue() const;

        protected:
            std::string name;
            Value *value;

            std::string nodeType = "VariableSetter";
        };
    }
}

#endif //CSSPREPROCESSOR_VARIABLESETTER_HPP
