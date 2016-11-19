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
            String(std::string value)
                : Value("Value/String"),
                  value(value) {}

            virtual const std::string debugString() const override;

            virtual const std::string generate(Generator *generator) override;

        protected:
            std::string value;
        };
    }
}


#endif //CSSPREPROCESSOR_STRING_HPP
