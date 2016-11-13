//
// Created by piotrek on 16.10.16.
//

#ifndef CSSPREPROCESSOR_SEPARATOR_HPP
#define CSSPREPROCESSOR_SEPARATOR_HPP

#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Separator : public Node {
        public:
            virtual const std::string toString() const override;

        protected:
            std::string nodeType = "Separator";
        };
    }
}

#endif //CSSPREPROCESSOR_SEPARATOR_HPP