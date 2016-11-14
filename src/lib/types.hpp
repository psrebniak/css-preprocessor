#ifndef CSSPREPROCESSOR_TYPES_HPP
#define CSSPREPROCESSOR_TYPES_HPP

#include <utility>
#include <map>
#include <vector>

#include "lib/ast/node/Node.hpp"

typedef std::map<std::string, std::vector<CSSP::AST::Node *>> FileToTreeMapType;
typedef std::pair<std::string, std::vector<CSSP::AST::Node *>> FileToTreePairType;
typedef std::vector<CSSP::AST::Node *> NodeVectorType;

#endif //CSSPREPROCESSOR_TYPES_HPP
