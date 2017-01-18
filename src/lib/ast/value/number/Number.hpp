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
            /**
             * Constructor
             */
            Number(std::string);

            virtual ~Number() = default;

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

            /**
             * Get number unit (eg. px)
             * @return
             */
            const std::string getUnit() const {
                return this->unit;
            }

            /**
             * Get value without unit
             * @return
             */
            const float getValue() const {
                return this->number;
            }

            /**
             * Helper method, return float without trailing zeroes
             * @param number
             * @return
             */
            static const std::string floatToString(float number);

        protected:
            /**
             * number value
             */
            float number;

            /**
             * unit
             */
            std::string unit;
        };
    }
}

#endif //CSSPREPROCESSOR_NUMBER_HPP
