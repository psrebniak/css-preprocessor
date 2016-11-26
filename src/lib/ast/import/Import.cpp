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
        return "// Import file: " + this->getFilename() + generator->getEol();
    }

    generator->registerError("Cannot find file: " + this->getFilename());
    return std::string();
}
