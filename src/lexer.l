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
    yylval->build <std::string> (yytext);
    return token::RAW_STRING;
}
\'{1}([^\']|\\\')*\'{1} {
    yylval->build <std::string> (yytext);
    return token::RAW_STRING;
}

{DIGIT}+ {
    yylval->build <std::string> (yytext);
    return token::NUMBER;
}

{HEX}{6} {
    yylval->build <std::string> (yytext);
    return token::HEX;
}

{HEX}{3} {
    yylval->build <std::string> (yytext);
    return token::HEX;
}

{STRING}+ {
    yylval->build <std::string> (yytext);
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
    lexerVirtualWhiteSpaceDetected = 1;
}
\n {
    loc->lines();
    //return( token::NEW_LINE );
}

. {
    yylval->build <std::string> (yytext);
    return token::CHAR;
}

%%
