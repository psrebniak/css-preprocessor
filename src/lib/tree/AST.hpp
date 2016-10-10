//
// Created by piotrek on 10.10.16.
//

#ifndef CSSPREPROCESSOR_AST_HPP
#define CSSPREPROCESSOR_AST_HPP

#include <string>

class AST {
public:
    virtual std::string toString() = 0;

private:

};


#endif //CSSPREPROCESSOR_AST_HPP
