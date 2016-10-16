%{
    #include <string>
    #include "lib/lexer/Lexer.hpp"

    using token = CSSP::Parser::token;

    #undef  YY_DECL
    #define YY_DECL int CSSP::Scanner::yylex( CSSP::Parser::semantic_type * const lval, CSSP::Parser::location_type *location )
    #define yyterminate() return( token::END )
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
%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

"//"+(.|"\\\n")*	;// ignore c-style comments
\/\*+([^*]|[ \t\r\n]|(\*+([^\*\/]|[ \t\r\n])))*\*+\/ ; // ignore c++-style comments

\"{1}([^\"]|"\\\"")*\"{1} {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::RAW_STRING);
    return token::RAW_STRING;
}
\'{1}([^\']|\\\')*\'{1} {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::RAW_STRING);
    lexerWhitespaceFlag = false;
    return token::RAW_STRING;
}

{DIGIT}+ {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::NUMBER);
    lexerWhitespaceFlag = false;
    return token::NUMBER;
}

{HEX}{6} {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::HEX);
    lexerWhitespaceFlag = false;
    return token::HEX;
}

{HEX}{3} {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::HEX);
    lexerWhitespaceFlag = false;
    return token::HEX;
}

{STRING}+ {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::STRING);
    lexerWhitespaceFlag = false;
    return token::STRING;
}

"~" {
    return token::TILDE;
}
"!" {
    return token::BANG;
}
"@" {
    return token::AT;
}
"#" {
    return token::HASH;
}
"$" {
    return token::DOLLAR;
}
"%" {
    return token::PERCENT;
}
"^" {
    return token::CARET;
}
"&" {
    return token::AMP;
}
"*" {
    return token::ASTERISK;
}
"(" {
    return token::LPAREN;
}
")" {
    return token::RPAREN;
}

"-" {
    //@warn always tokenized as STRING
    return token::MINUS;
}
"_" {
    //@warn always tokenized as STRING
    return token::UNDERSCORE;
}
"+" {
    return token::PLUS;
}
"=" {
    return token::EQUAL;
}
"[" {
    return token::LBRACKET;
}
"]" {
    return token::RBRACKET;
}
"{" {
    return token::LBRACE;
}
"}" {
    return token::RBRACE;
}
":" {
    return token::COLON;
}
";" {
    return token::SEMICOLON;
}
"," {
    return token::COMMA;
}
"." {
    return token::DOT;
}
"<" {
    return token::LT;
}
">" {
    return token::GT;
}
"?" {
    return token::QUESTION;
}
"/" {
    return token::DIVIDE;
}

(\ |\t)+  {
    lexerWhitespaceFlag = true;
}
\n {
    loc->lines();
}

. {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::CHAR);
    return yytext[0];
}

%%
