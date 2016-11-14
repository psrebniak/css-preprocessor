#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#if !defined(yyFlexLexerOnce)

#include <FlexLexer.h>

#endif

#include "generated/parser.hpp"
#include "generated/location.hh"

namespace CSSP {

    class Lexer : public yyFlexLexer {
    public:
        Lexer(std::istream *in) : yyFlexLexer(in) {
            loc = new CSSP::Parser::location_type();
        };

        virtual ~Lexer() {
            delete loc;
        };

        using FlexLexer::yylex;

        // created by flex
        virtual int yylex(CSSP::Parser::semantic_type *const lval,
                          CSSP::Parser::location_type *location);

        CSSP::Parser::location_type &getCurrentLocation() {
            return *(this->loc);
        }


    private:
        bool lexerWhitespaceFlag = false;

        /* yyval ptr */
        CSSP::Parser::semantic_type *yylval = nullptr;

        /* location ptr */
        CSSP::Parser::location_type *loc = nullptr;
    };

}

#endif
