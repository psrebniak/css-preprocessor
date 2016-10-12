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
            Color(std::string color)
                : value(color) {};

            Color(float red, float green, float blue, float aplha = 1)
                : red(red), green(green), blue(blue), alpha(alpha) {};

            virtual const std::string toString() const override;

        protected:
            float red;
            float green;
            float blue;
            float alpha;
            std::string value;

            std::string nodeType = "Color";
        };
    }
}


#endif //CSSPREPROCESSOR_COLOR_HPP
