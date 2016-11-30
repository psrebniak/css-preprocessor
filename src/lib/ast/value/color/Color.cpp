//
// Created by piotrek on 11.10.16.
//

#include <list>
#include <sstream>
#include <iterator>
#include "Color.hpp"

const std::string CSSP::AST::Color::debugString() const {
    if (this->value != "") {
        return "#" + this->value;
    }

    std::list<std::string> list = {};
    list.push_back(this->alpha != 0 ? "rgba(" : "rgb(");

    list.push_back(std::to_string(this->red));
    list.push_back(",");

    list.push_back(std::to_string(this->green));
    list.push_back(",");

    list.push_back(std::to_string(this->blue));
    list.push_back(")");

    std::stringstream res;
    std::copy(list.begin(), list.end(), std::ostream_iterator<std::string>(res));
    return res.str();
}

const std::string CSSP::AST::Color::generate(CSSP::Generator *generator) const {
    return this->debugString();
}
