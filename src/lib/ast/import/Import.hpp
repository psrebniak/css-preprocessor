//
// Created by piotrek on 18.10.16.
//

#ifndef CSSPREPROCESSOR_IMPORT_HPP
#define CSSPREPROCESSOR_IMPORT_HPP

#include "lib/ast/node/Node.hpp"

namespace CSSP {
    namespace AST {
        class Import : public Node {
        public:
            Import(std::string path)
                : path(path) {};

            virtual const std::string toString() const override;

        protected:
            std::string path;

            std::string nodeType = "Import";
        };
    }
}



#endif //CSSPREPROCESSOR_IMPORT_HPP
