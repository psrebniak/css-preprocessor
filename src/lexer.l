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

DIGIT    [0-9]
ID       [a-zA-Z0-9\-\_]
TAG      [a-zA-Z]
PROPERTY [a-zA-Z\-]
MODIFIER [a-z]
UNIT     ("px"|"em"|"rem"|"%")
%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}



{TAG}+          {
                    yylval->build <std::string> (yytext);
                    return token::TAG;
                }
"."{ID}+        {
                    yylval->build <std::string> (yytext);
                    return token::CLASS;
                }
"#"{ID}+        {
                    yylval->build <std::string> (yytext);
                    return token::ID;
                }
":"{PROPERTY}+       {
                    yylval->build <std::string> (yytext);
                    return token::PSEUDO_CLASS;
                }
"::"{PROPERTY}+      {
                    yylval->build <std::string> (yytext);
                    return token::PSEUDO_ELEMENT;
                }
"#{$"{ID}+"}"   {
                    yylval->build <std::string> (yytext);
                    return token::VARIABLE_NAME;
                }
"$"{ID}+        {
                    yylval->build <std::string> (yytext);
                    return token::VARIABLE_NAME;
                }
{PROPERTY}+     {
                    yylval->build <std::string> (yytext);
                    return token::PROPERTY_NAME;
                }
"!"{MODIFIER}+  {
                    yylval->build <std::string> (yytext);
                    return token::MODIFIER;
                }
{DIGIT}+{UNIT}   {
                    yylval->build <std::string> (yytext);
                    return token::UNIT_VALUE;
                }

[\+\~\>]        {
                        yylval->build <std::string> (yytext);
                        return token::SELECTOR_SEPARATOR;
                    }

[a-zA-Z]+     {
                yylval->build< std::string >( yytext );
                return( token::WORD );
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
