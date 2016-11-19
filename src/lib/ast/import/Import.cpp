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
        return "// Import file: " + this->getFilename();
    }

    generator->registerError("Cannot find file: " + this->getFilename());
    return Node::generate(generator);
}
