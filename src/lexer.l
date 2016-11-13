%{
    #include <string>
    #include "lib/lexer/Lexer.hpp"

    #undef  YY_DECL
    #define YY_DECL int CSSP::Lexer::yylex( CSSP::Parser::semantic_type * const lval, CSSP::Parser::location_type *location )

    using token = CSSP::Parser::token;

    #define yyterminate() return( token::END )

    #define YY_NO_UNISTD_H

    #define YY_USER_ACTION loc->step(); loc->columns(yyleng);
%}

%option debug
%option nodefault
%option yyclass="CSSP::Lexer"
%option noyywrap
%option c++
%option verbose

HEX      [0-9a-fA-F]
DIGIT    [0-9]
STRING   [a-zA-Z0-9\-\_]

%%
%{
            yylval = lval;
%}

"@import" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::IMPORT);
    lexerWhitespaceFlag = false;
    return token::IMPORT;
}

"@media" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::MEDIA);
    lexerWhitespaceFlag = false;
    return token::MEDIA;
}

"//"+(.|"\\\n")*	;// ignore c-style comments
\/\*+([^*]|[ \t\r\n]|(\*+([^\*\/]|[ \t\r\n])))*\*+\/ ; // ignore c++-style comments

\"{1}([^\"]|"\\\"")*\"{1} {
    std::string text = yytext;
    text = text.substr(1, text.length() - 2);
    yylval->build <CSSP::Token>() = CSSP::Token(text, lexerWhitespaceFlag, token::RAW_STRING);
    return token::RAW_STRING;
}
\'{1}([^\']|\\\')*\'{1} {
    std::string text = yytext;
    text = text.substr(1, text.length() - 2);
    yylval->build <CSSP::Token>() = CSSP::Token(text, lexerWhitespaceFlag, token::RAW_STRING);
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
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::TILDE);
    lexerWhitespaceFlag = false;
    return token::TILDE;
}
"!" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::BANG);
    lexerWhitespaceFlag = false;
    return token::BANG;
}
"@" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::AT);
    lexerWhitespaceFlag = false;
    return token::AT;
}
"#" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::HASH);
    lexerWhitespaceFlag = false;
    return token::HASH;
}
"$" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::DOLLAR);
    lexerWhitespaceFlag = false;
    return token::DOLLAR;
}
"%" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::PERCENT);
    lexerWhitespaceFlag = false;
    return token::PERCENT;
}
"^" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::CARET);
    lexerWhitespaceFlag = false;
    return token::CARET;
}
"&" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::AMP);
    lexerWhitespaceFlag = false;
    return token::AMP;
}
"*" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::ASTERISK);
    lexerWhitespaceFlag = false;
    return token::ASTERISK;
}
"(" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::LPAREN);
    lexerWhitespaceFlag = false;
    return token::LPAREN;
}
")" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::RPAREN);
    lexerWhitespaceFlag = false;
    return token::RPAREN;
}

"-" {
    //@warn always tokenized as STRING
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::MINUS);
    lexerWhitespaceFlag = false;
    return token::MINUS;
}
"_" {
    //@warn always tokenized as STRING
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::UNDERSCORE);
    lexerWhitespaceFlag = false;
    return token::UNDERSCORE;
}
"+" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::PLUS);
    lexerWhitespaceFlag = false;
    return token::PLUS;
}
"=" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::EQUAL);
    lexerWhitespaceFlag = false;
    return token::EQUAL;
}
"[" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::LBRACKET);
    lexerWhitespaceFlag = false;
    return token::LBRACKET;
}
"]" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::RBRACKET);
    lexerWhitespaceFlag = false;
    return token::RBRACKET;
}
"{" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::LBRACE);
    lexerWhitespaceFlag = false;
    return token::LBRACE;
}
"}" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::RBRACE);
    lexerWhitespaceFlag = false;
    return token::RBRACE;
}
":" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::COLON);
    lexerWhitespaceFlag = false;
    return token::COLON;
}
";" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::SEMICOLON);
    lexerWhitespaceFlag = false;
    return token::SEMICOLON;
}
"," {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::COMMA);
    lexerWhitespaceFlag = false;
    return token::COMMA;
}
"." {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::DOT);
    lexerWhitespaceFlag = false;
    return token::DOT;
}
"<" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::LT);
    lexerWhitespaceFlag = false;
    return token::LT;
}
">" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::GT);
    lexerWhitespaceFlag = false;
    return token::GT;
}
"?" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::QUESTION);
    lexerWhitespaceFlag = false;
    return token::QUESTION;
}
"/" {
    yylval->build <CSSP::Token>() = CSSP::Token(yytext, lexerWhitespaceFlag, token::DIVIDE);
    lexerWhitespaceFlag = false;
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
