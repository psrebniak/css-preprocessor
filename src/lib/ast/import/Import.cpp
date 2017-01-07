//
// Created by piotrek on 18.10.16.
//

#include "lib/generator/Generator.hpp"
#include "Import.hpp"

const std::string CSSP::AST::Import::debugString() const {
    return "@import" + this->path + ";\n";
}

const std::string CSSP::AST::Import::generate(CSSP::Generator *generator) const {
    if (generator->pushFile(this->getRealPath())) {
        if (generator->isMinified()) {
            return std::string();
        }

        return generator->isMinified() ?
               std::string() :
               "// Import file: " + this->getFilename() + generator->getEol();
    }

    generator->registerError("Cannot process file: " + this->getFilename() + ". Use Css @import fallback. ");
    return "@import " + this->getFilename() + ";" + generator->getEol();
}
