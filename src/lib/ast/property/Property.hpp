//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_PROPERTY_HPP
#define CSSPREPROCESSOR_PROPERTY_HPP

#include <vector>
#include <string>

#include "lib/types.hpp"
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Property : public Node {
        public:
            Property(Node *name, NodeVectorType *valueList, Node *modifier)
                : Node("Property"),
                  name(name),
                  valueList(valueList),
                  modifier(modifier) {}

            virtual const std::string generate(Generator *generator) const override;

            virtual const std::string debugString() const override;

        protected:
            Node *name;
            NodeVectorType *valueList;
            Node *modifier;
        };
    }
}

#endif //CSSPREPROCESSOR_PROPERTY_HPP
