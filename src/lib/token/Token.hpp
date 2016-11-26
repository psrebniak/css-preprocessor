//
// Created by piotrek on 16.10.16.
//

#ifndef CSSPREPROCESSOR_TOKEN_HPP
#define CSSPREPROCESSOR_TOKEN_HPP

#include <string>

namespace CSSP {
    class Token {
    public:
        Token() {};

        Token(std::string stringValue, bool isWhitespacePrefixed, int tokenType)
            : stringValue(stringValue),
              whitespacePrefixed(isWhitespacePrefixed),
              tokenType(tokenType) {};

        const std::string toString() const;

        const bool isWhitespacePrefixed() const;

        const int getTokenType() const;

    protected:
        /**
         * token string
         */
        std::string stringValue;

        /**
         * was whitespace before token
         */
        bool whitespacePrefixed;

        /**
         * int token type from parser.y
         */
        int tokenType;
    };
}

#endif //CSSPREPROCESSOR_TOKEN_HPP
