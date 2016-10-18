//
// Created by piotrek on 18.10.16.
//

#include "Import.hpp"

const std::string CSSP::AST::Import::toString() const {
    return "@import" + this->path + ";\n";
}
