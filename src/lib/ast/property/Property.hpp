//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_PROPERTY_HPP
#define CSSPREPROCESSOR_PROPERTY_HPP

#include <list>
#include <string>

#include "lib/types.hpp"
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Property : public Node {
        public:
            /**
             * Constructor
             * @param name
             * @param valueList
             * @param modifier
             * @param minify
             */
            Property(Node *name, NodeListType *valueList, Node *modifier, bool minify = false)
                : Node("Property"),
                  name(name),
                  valueList(valueList),
                  modifier(modifier) {}

            virtual ~Property();

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

        protected:
            /**
             * property name
             */
            Node *name;

            /**
             * property values
             */
            NodeListType *valueList;

            /**
             * Modifier
             */
            Node *modifier;
        };
    }
}

#endif //CSSPREPROCESSOR_PROPERTY_HPP
