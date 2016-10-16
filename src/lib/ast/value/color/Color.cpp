//
// Created by piotrek on 11.10.16.
//

#include <vector>
#include <sstream>
#include <iterator>
#include "Color.hpp"

const std::string CSSP::AST::Color::toString() const {
    if (this->value != "") {
        return "#" + this->value;
    }
    std::string retval = "";
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
