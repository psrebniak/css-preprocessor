//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_COLOR_HPP
#define CSSPREPROCESSOR_COLOR_HPP

#include "lib/ast/value/value/Value.hpp"

namespace CSSP {
    namespace AST {
        class Color : public Value {
        public:
            /**
             * Constructor
             * @param color
             */
            Color(std::string color)
                : Value("Value/Color"),
                  value(color) {};

            virtual ~Color() = default;

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
             * Color value
             */
            std::string value;
        };
    }
}


#endif //CSSPREPROCESSOR_COLOR_HPP
