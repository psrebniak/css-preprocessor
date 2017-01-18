//
// Created by piotrek on 16.10.16.
//

#ifndef CSSPREPROCESSOR_SELECTOR_HPP
#define CSSPREPROCESSOR_SELECTOR_HPP

#include <list>
#include <map>
#include <lib/ast/value/value/Value.hpp>
#include "lib/ast/node/Node.hpp"
#include "lib/ast/value/variable/Variable.hpp"

namespace CSSP {
    namespace AST {

        class Selector : public Node {
        public:

            /**
             * Selector type
             */
            enum SelectorType {
                TAG,
                CLASS,
                ID,
                PSEUDOCLASS,
                PSEUDOELEMENT,
                ATTRIBUTE,
                ATTRIBUTE_VALUE,
                ASTERISK
            };

            /**
             * Constructor
             * @param type
             * @param name
             * @param value
             * @param variable
             */
            Selector(SelectorType type, std::string name, Value *value = nullptr, Variable *variable = nullptr)
                : Node("Selector"),
                  type(type),
                  name(name),
                  value(value),
                  variable(variable) {};

            ~Selector();

            /**
             * Return selector type as string
             * @return
             */
            std::string getSelectorType() const;

            /**
             * Get prefix for current selector type
             * @return
             */
            std::string getSelectorPrefix() const;

            /**
             * @inherit0
             * @return
             */
            virtual const std::string debugString() const override;

            /**
             * @inherit
             * @param generator
             * @return
             */
            virtual const std::string generate(Generator *generator) const override;

        protected:
            /**
             * Selector type
             */
            SelectorType type;

            /**
             * Selector name
             */
            std::string name;

            /**
             * attribute value
             */
            Value *value;

            /**
             * Associated variable (used only with [data-tags]
             */
            Variable *variable;

            /**
             * SelectorType to String/Prefix map
             */
            std::map<SelectorType, std::pair<std::string, std::string> > selectorToStringMap = {
                {TAG,             std::pair<std::string, std::string>("TAG", "")},
                {CLASS,           std::pair<std::string, std::string>("CLASS", ".")},
                {ID,              std::pair<std::string, std::string>("ID", "#")},
                {PSEUDOCLASS,     std::pair<std::string, std::string>("PSEUDOCLASS", ":")},
                {PSEUDOELEMENT,   std::pair<std::string, std::string>("PSEUDOELEMENT", "::")},
                {ATTRIBUTE,       std::pair<std::string, std::string>("ATTRIBUTE", "[")},
                {ATTRIBUTE_VALUE, std::pair<std::string, std::string>("ATTRIBUTE_VALUE", "[")},
                {ASTERISK,        std::pair<std::string, std::string>("ASTERISK", "")}
            };
        };
    }
}


#endif //CSSPREPROCESSOR_SELECTOR_HPP
