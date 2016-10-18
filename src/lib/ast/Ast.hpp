//
// Created by piotrek on 11.10.16.
//

#ifndef CSSPREPROCESSOR_AST_HPP
#define CSSPREPROCESSOR_AST_HPP

#include "lib/ast/node/Node.hpp"
#include "lib/ast/modifier/Modifier.hpp"
#include "lib/ast/property/Property.hpp"
#include "lib/ast/separator/Separator.hpp"
#include "lib/ast/selector/Selector.hpp"
#include "lib/ast/block/Block.hpp"
#include "lib/ast/import/Import.hpp"
#include "lib/ast/variableSetter/VariableSetter.hpp"

// value
#include "lib/ast/value/value/Value.hpp"
#include "lib/ast/value/color/Color.hpp"
#include "lib/ast/value/number/Number.hpp"
#include "lib/ast/value/string/String.hpp"
#include "lib/ast/value/variable/Variable.hpp"
#include "lib/ast/value/calculation/Calculation.hpp"

#endif //CSSPREPROCESSOR_AST_HPP
