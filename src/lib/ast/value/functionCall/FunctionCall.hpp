//
// Created by piotrek on 26.01.17.
//

#ifndef CSSP_FUNCTIONCALL_HPP
#define CSSP_FUNCTIONCALL_HPP

#include <list>
#include <string>
#include "lib/types.hpp"
#include "lib/ast/value/value/Value.hpp"

namespace CSSP {
    namespace AST {
        class FunctionCall : public Value {
        public:
            FunctionCall(std::string functionName, NodeListType *valueList)
                : Value("FunctionCall"),
                  functionName(functionName),
                  valueList(valueList) {};

            virtual ~FunctionCall();

            const std::string generate(Generator *generator) const;

        protected:
            std::string functionName;
            NodeListType *valueList;
        };
    }
}


#endif //CSSP_FUNCTIONCALL_HPP
