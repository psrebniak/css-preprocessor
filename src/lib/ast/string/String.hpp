//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_STRING_HPP
#define CSSPREPROCESSOR_STRING_HPP

#include <string>
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class String : public Node {
        public:
            String(std::string value)
                : value(value) {}

            virtual const std::string toString() const override;

        protected:
            std::string value;

            std::string nodeType = "String";
        };
    }
}



#endif //CSSPREPROCESSOR_STRING_HPP
