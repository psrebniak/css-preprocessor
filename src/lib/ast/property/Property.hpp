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
                : name(name),
                  valueList(valueList),
                  modifier(modifier) {};

            virtual const std::string toString() const override;

        protected:
            Node *name;
            NodeVectorType *valueList;
            Node *modifier;

            std::string nodeType = "Property";
        };
    }
}

#endif //CSSPREPROCESSOR_PROPERTY_HPP
