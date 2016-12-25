//
// Created by piotrek on 05.11.16.
//

#ifndef CSSPREPROCESSOR_MEDIAENTRY_HPP
#define CSSPREPROCESSOR_MEDIAENTRY_HPP

#include "lib/ast/node/Node.hpp"
#include "lib/ast/value/value/Value.hpp"

namespace CSSP {
    namespace AST {
        class MediaEntry : public Node {
        public:
            /**
             * Constructor
             * @param name
             * @param value
             */
            MediaEntry(std::string name, Value *value)
                : Node("MediaEntry"),
                  name(name),
                  value(value) {};

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
             * Media entry name (eg. min-width)
             */
            std::string name;

            /**
             * Media entry value (nullable)
             */
            Value *value;
        };
    }
}

#endif //CSSPREPROCESSOR_MEDIAENTRY_HPP
