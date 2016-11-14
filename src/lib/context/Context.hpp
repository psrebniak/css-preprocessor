#ifndef CSSPREPROCESSOR_CONTEXT_HPP
#define CSSPREPROCESSOR_CONTEXT_HPP

#include <map>
#include <vector>
#include <string>
#include <sstream>

#include "lib/ast/node/Node.hpp"
#include "lib/ast/value/value/Value.hpp"
#include "lib/ast/variableSetter/VariableSetter.hpp"

#include "lib/driver/Driver.hpp"

namespace CSSP {
    class Context {
    public:
        Context() = default;

        bool setVariable(AST::VariableSetter *variable);

        unsigned int generateCode(std::stringstream output, std::vector<AST::Node *> *instructionList);

    protected:
        std::map<std::string, const AST::Value *> variables;
    };
}

#endif //CSSPREPROCESSOR_CONTEXT_HPP
