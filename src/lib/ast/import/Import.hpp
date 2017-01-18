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
            /**
             * Import class
             * @param path
             * @param realpath
             */
            Import(std::string path, std::string realpath)
                : Node("Import"),
                  path(path),
                  realpath(realpath) {};

            virtual ~Import() = default;

            /**
             * @inherit
             * @return
             */
            virtual const std::string debugString() const override;

            /**
             * @inherit
             * @param generator
             * @return
             */
            virtual const std::string generate(Generator *generator) const override;

            /**
             * Return given filename string
             * @return
             */
            const std::string getFilename() const {
                return this->path;
            }

            /**
             * get real path
             * @return
             */
            const std::string getRealPath() const {
                return this->realpath;
            }

        protected:
            /**
             * path (grammar parameter)
             */
            std::string path;

            /**
             * Real path that reflect absolute path of path
             */
            std::string realpath;
        };
    }
}


#endif //CSSPREPROCESSOR_IMPORT_HPP
