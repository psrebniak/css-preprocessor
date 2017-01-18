//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_NODE_HPP
#define CSSPREPROCESSOR_NODE_HPP

#include <string>
#include "lib/token/Token.hpp"

namespace CSSP {

    // forward declaration
    class Generator;

    namespace AST {

        /**
         * Base Abstrack Syntax Tree class
         */
        class Node {
        public:
            /**
             *
             * @param nodeType string determine node type
             */
            Node(std::string nodeType)
                : nodeType(nodeType) {};

            virtual ~Node() = default;

            /**
             * Generate denode debug string and return it
             * @return
             */
            virtual const std::string debugString() const = 0;

            /**
             * Returns node type passed with constructor
             * @return node type
             */
            const std::string &getNodeType() const;

            /**
             * Set token that create current AST node
             * @return
             */
            virtual Node *setToken(CSSP::Token);

            /**
             * Return token associated with current AST node
             * @return
             */
            CSSP::Token getToken() const;

            /**
             * Generate output code, can use generator instance to get access to context information
             * @param generator
             * @return output string
             */
            virtual const std::string generate(Generator *generator) const {
                return "";
            };

        protected:
            /**
             * String that describe current node type (for debugging purposes only)
             */
            std::string nodeType = "Unknown";

            /**
             * Token associated with current Node
             */
            CSSP::Token token;

        };
    }
}


#endif //CSSPREPROCESSOR_NODE_HPP
