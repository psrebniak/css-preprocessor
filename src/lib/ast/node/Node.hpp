//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_NODE_HPP
#define CSSPREPROCESSOR_NODE_HPP

#include <string>

namespace CSSP {
    namespace AST {

        class Node {

        public:
            virtual const std::string toString() const = 0;
            const std::string &getNodeType() const;

#ifdef DEBUG
            virtual const bool test() const = 0;
#endif

        protected:
            std::string nodeType = "Unknown";

        };
    }
}


#endif //CSSPREPROCESSOR_NODE_HPP
