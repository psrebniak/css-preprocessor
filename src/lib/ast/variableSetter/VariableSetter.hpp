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
            /**
             * Constructor
             * @param name
             * @param value
             */
            VariableSetter(std::string name, Value *value)
                : Node("VariableSetter"),
                  name(name),
                  value(value) {}

            virtual ~VariableSetter();

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

            /**
             * Get variable name
             * @return
             */
            const std::string getName() const;

            /**
             * Get variable value
             * @return
             */
            Value *getValue() const;

        protected:
            /**
             * variable name
             */
            std::string name;

            /**
             * variable value
             */
            Value *value;
        };
    }
}

#endif //CSSPREPROCESSOR_VARIABLESETTER_HPP
