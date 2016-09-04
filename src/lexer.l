%{
    #include <string>
    #include "lib/lexer/Lexer.hpp"

    using token = CSSP::Parser::token;

    #undef  YY_DECL
    #define YY_DECL int CSSP::Scanner::yylex( CSSP::Parser::semantic_type * const lval, CSSP::Parser::location_type *location )
    //#define yyterminate() return( token::END_OF_FILE )
    #define YY_USER_ACTION loc->step(); loc->columns(yyleng);
%}

%option debug
%option nodefault
%option yyclass="CSSP::Scanner"
%option noyywrap
%option c++
%option verbose

HEX      [0-9a-fA-F]
DIGIT    [0-9]
STRING   [a-zA-Z0-9\-\_]

ID       [a-zA-Z0-9\-\_]
TAG      [a-zA-Z]
PROPERTY [a-zA-Z\-]
MODIFIER [a-z]
UNIT     ("px"|"em"|"rem"|"%")
%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

{HEX}{6} {
    yylval->build <std::string> (yytext);
    return token::HEX;
}

{HEX}{3} {
    yylval->build <std::string> (yytext);
    return token::HEX;
}

{DIGIT}+ {
    yylval->build <std::string> (yytext);
    return token::NUMBER;
}

{STRING}+ {
    yylval->build <std::string> (yytext);
    return token::STRING;
}


[\+\~\>]        {
                        yylval->build <std::string> (yytext);
                        return token::SELECTOR_SEPARATOR;
                    }


\n            {
                // Update line number
                loc->lines();
                //return( token::NEW_LINE );
              }

\:            {
                return token::COLON;
              }

\;            {
                return token::SEMICOLON;
              }
\,            {
                return token::COMMA;
              }
\(            {
                return token::LPAREN;
              }

\)            {
                return token::RPAREN;
              }

\{            {
                return token::LBRACKET;
              }

\}            {
                return token::RBRACKET;
              }
" "+          ;
.             {
                return( token::CHAR );
              }
%%
