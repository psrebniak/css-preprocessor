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
            MediaEntry(std::string name, Value *value)
                : name(name),
                  value(value) {};

            virtual const std::string toString() const override;

        protected:
            std::string name;
            Value *value;

            std::string nodeType = "MediaEntry";
        };
    }
}

#endif //CSSPREPROCESSOR_MEDIAENTRY_HPP
