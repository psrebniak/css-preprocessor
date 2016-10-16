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
            virtual const std::string toString() const = 0;
            const std::string &getNodeType() const;

            virtual Node* setToken(CSSP::Token);

#ifdef DEBUG
            virtual const bool test() const = 0;
#endif

        protected:
            std::string nodeType = "Unknown";
            CSSP::Token token;

        };
    }
}


#endif //CSSPREPROCESSOR_NODE_HPP
