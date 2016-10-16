//
// Created by piotrek on 16.10.16.
//

#ifndef CSSPREPROCESSOR_TOKEN_HPP
#define CSSPREPROCESSOR_TOKEN_HPP

#include <string>

namespace CSSP {
    class Token {
    public:
        const std::string toString() const;
        const bool isWhitespacePrefixed() const;
        const int getTokenType() const;

        Token(){};
        Token(std::string stringValue, bool isWhitespacePrefixed, int tokenType)
            : stringValue(stringValue),
              whitespacePrefixed(isWhitespacePrefixed),
              tokenType(tokenType) {};

    protected:
        std::string stringValue;
        bool whitespacePrefixed;
        int tokenType;
    };
}

#endif //CSSPREPROCESSOR_TOKEN_HPP
