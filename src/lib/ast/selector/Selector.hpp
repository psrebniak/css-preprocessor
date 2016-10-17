//
// Created by piotrek on 16.10.16.
//

#ifndef CSSPREPROCESSOR_SELECTOR_HPP
#define CSSPREPROCESSOR_SELECTOR_HPP

#include <vector>
#include <map>
#include <lib/ast/value/value/Value.hpp>
#include "lib/ast/node/Node.hpp"


namespace CSSP {
    namespace AST {

        class Selector : public Node {
        public:

            enum SelectorType {
                TAG,
                CLASS,
                ID,
                PSEUDOCLASS,
                PSEUDOELEMENT,
                ATTRIBUTE,
                ATTRIBUTE_VALUE
            };

            Selector(SelectorType type, std::string name, Value* value= NULL)
                : type(type),
                  name(name),
                  value(value) {};

            std::string getSelectorType() const;
            std::string getSelectorPrefix() const;


            virtual const std::string toString() const override;

        protected:
            SelectorType type;
            std::string name;
            Value* value;

            std::map<SelectorType, std::pair<std::string, std::string>> selectorToStringMap = {
                {TAG, std::pair<std::string, std::string>("TAG", "")},
                {CLASS, std::pair<std::string, std::string>("CLASS", ".")},
                {ID, std::pair<std::string, std::string>("ID", "#")},
                {PSEUDOCLASS, std::pair<std::string, std::string>("PSEUDOCLASS", ":")},
                {PSEUDOELEMENT, std::pair<std::string, std::string>("PSEUDOELEMENT", "::")},
                {ATTRIBUTE, std::pair<std::string, std::string>("ATTRIBUTE", "[")},
                {ATTRIBUTE_VALUE, std::pair<std::string, std::string>("ATTRIBUTE_VALUE", "[")}
            };
        };
    }
}


#endif //CSSPREPROCESSOR_SELECTOR_HPP
