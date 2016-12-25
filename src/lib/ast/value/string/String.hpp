//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_STRING_HPP
#define CSSPREPROCESSOR_STRING_HPP

#include <string>
#include "lib/ast/value/value/Value.hpp"

namespace CSSP {
    namespace AST {
        class String : public Value {
        public:
            /**
             * Constructor
             * @param value
             */
            String(std::string value)
                : Value("Value/String"),
                  value(value) {}

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
             * string value
             */
            std::string value;
        };
    }
}


#endif //CSSPREPROCESSOR_STRING_HPP
