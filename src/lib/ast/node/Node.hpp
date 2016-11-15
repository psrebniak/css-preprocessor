//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_NODE_HPP
#define CSSPREPROCESSOR_NODE_HPP

#include <string>
#include <lib/token/Token.hpp>

namespace CSSP {
    namespace AST {

        class Node {
        public:
            Node(std::string nodeType)
                : nodeType(nodeType) {};

            virtual const std::string toString() const = 0;

            const std::string &getNodeType() const;

            virtual Node *setToken(CSSP::Token);

            CSSP::Token getToken() const;

        protected:
            std::string nodeType = "Unknown";
            CSSP::Token token;

        };
    }
}


#endif //CSSPREPROCESSOR_NODE_HPP
