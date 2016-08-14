#ifndef __SCANNER_HPP__
#define __SCANNER_HPP__

#if !defined(yyFlexLexerOnce)

#include <FlexLexer.h>

#endif

#include "generated/parser.hpp"
#include "generated/location.hh"

namespace CSSP {

    class Scanner : public yyFlexLexer {
    public:

        Scanner(std::istream *in) : yyFlexLexer(in) {
            loc = new CSSP::Parser::location_type();
        };

        virtual ~Scanner() {
            delete loc;
        };

        using FlexLexer::yylex;

        // created by flex
        virtual int yylex(CSSP::Parser::semantic_type *const lval,
                  CSSP::Parser::location_type *location);


    private:
        /* yyval ptr */
        CSSP::Parser::semantic_type *yylval = nullptr;
        /* location ptr */
        CSSP::Parser::location_type *loc = nullptr;
    };

}

#endif
