//
// Created by piotrek on 11.10.16.
//

#include <vector>
#include <sstream>
#include <iterator>
#include "Color.hpp"

const std::string CSSP::AST::Color::debugString() const {
    if (this->value != "") {
        return "#" + this->value;
    }

    std::vector<std::string> vector = {};
    vector.push_back(this->alpha != 0 ? "rgba(" : "rgb(");

    vector.push_back(std::to_string(this->red));
    vector.push_back(",");

    vector.push_back(std::to_string(this->green));
    vector.push_back(",");

    vector.push_back(std::to_string(this->blue));
    vector.push_back(")");

    std::stringstream res;
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<std::string>(res));
    return res.str();
}

const std::string CSSP::AST::Color::generate(CSSP::Generator *generator) {
    return this->debugString();
}
