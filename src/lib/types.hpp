#ifndef CSSPREPROCESSOR_TYPES_HPP
#define CSSPREPROCESSOR_TYPES_HPP

#include <utility>
#include <map>
#include <vector>

#include "lib/ast/node/Node.hpp"
#include "lib/ast/value/value/Value.hpp"

typedef std::map<const std::string, std::vector<CSSP::AST::Node *>*> FileToTreeMapType;
typedef std::pair<const std::string, std::vector<CSSP::AST::Node *>*> FileToTreePairType;

typedef std::map<const std::string, CSSP::AST::Value*> NameToVariableMapType;
typedef std::pair<const std::string, CSSP::AST::Value*> NameToVariablePairType;

typedef std::vector<CSSP::AST::Node *> NodeVectorType;

#endif //CSSPREPROCESSOR_TYPES_HPP
