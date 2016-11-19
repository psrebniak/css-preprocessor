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
            Import(std::string path, std::string realpath)
                : Node("Import"),
                  path(path),
                  realpath(realpath) {};

            virtual const std::string debugString() const override;

            virtual const std::string generate(Generator *generator) const override;

            const std::string getFilename() const {
                return this->path;
            }

            const std::string getRealPath() const {
                return this->realpath;
            }

        protected:
            std::string path;
            std::string realpath;
        };
    }
}


#endif //CSSPREPROCESSOR_IMPORT_HPP
