%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace {CSSP}
%define parser_class_name {Parser}

%code requires {
   namespace CSSP {
      class Driver;
      class Lexer;
   }

   #include <map>
   #include <vector>

   #include "lib/types.hpp"
   #include "lib/ast/Ast.hpp"
   #include "lib/token/Token.hpp"
}

%parse-param { Lexer  &lexer  }
%parse-param { Driver  &driver  }

%code {
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   /* include for all driver functions */
   #include "lib/driver/Driver.hpp"

#undef yylex
#define yylex lexer.yylex
}

%define api.value.type variant
%define parse.assert
%define parse.error verbose

// TYPE TOKENS
%token <CSSP::Token> RAW_STRING

%token <CSSP::Token> HEX
%token <CSSP::Token> STRING
%token <CSSP::Token> NUMBER
%token <std::string> CHAR

// autogenerated tokens
%token END           0            "End of file"

// typeless tokens
%token <CSSP::Token> TILDE        "~"
%token <CSSP::Token> BANG         "!"
%token <CSSP::Token> AT           "@"
%token <CSSP::Token> HASH         "#"
%token <CSSP::Token> DOLLAR       "$"
%token <CSSP::Token> PERCENT      "%"
%token <CSSP::Token> CARET        "^"
%token <CSSP::Token> AMP          "&"
%token <CSSP::Token> ASTERISK     "*"
%token <CSSP::Token> LPAREN       "("
%token <CSSP::Token> RPAREN       ")"
%token <CSSP::Token> MINUS        "-"
%token <CSSP::Token> UNDERSCORE   "_"
%token <CSSP::Token> PLUS         "+"
%token <CSSP::Token> EQUAL        "="

%token <CSSP::Token> LBRACKET     "["
%token <CSSP::Token> RBRACKET     "]"
%token <CSSP::Token> LBRACE       "{"
%token <CSSP::Token> RBRACE       "}"

%token <CSSP::Token> COLON        ":"
%token <CSSP::Token> SEMICOLON    ";"
%token <CSSP::Token> COMMA        ","
%token <CSSP::Token> DOT          "."
%token <CSSP::Token> LT           "<"
%token <CSSP::Token> GT           ">"
%token <CSSP::Token> QUESTION     "?"
%token <CSSP::Token> DIVIDE       "/"

// special tokens
%token <CSSP::Token> IMPORT       "@import"
%token <CSSP::Token> FOR          "@for"
%token <CSSP::Token> MEDIA        "@media"

// modifiers
%type <CSSP::AST::Node*> modifier;

%type <CSSP::AST::Value*> value;
%type <CSSP::AST::Value*> valueVariable;
%type <CSSP::AST::Value*> valueString;
%type <CSSP::AST::Value*> valueNumber;
%type <CSSP::AST::Value*> valueCalculation;
%type <CSSP::AST::Value*> valueColor;

%type <std::vector<CSSP::AST::Node*>*> valueList;
%type <std::vector<CSSP::AST::Node*>*> selector;
%type <std::vector<CSSP::AST::Node*>*> globalInstructions;
%type <std::vector<CSSP::AST::Node*>*> instructions;
%type <std::vector<CSSP::AST::Node*>*> mediaList;

%type <CSSP::AST::Property*> property;
%type <CSSP::AST::Node*> selectorEntryType;
%type <CSSP::AST::Node*> selectorSeparator;
%type <CSSP::AST::Node*> selectorEntry;
%type <CSSP::AST::Node*> globalInstruction;
%type <CSSP::AST::Node*> instruction;
%type <CSSP::AST::Block*> block;
%type <CSSP::AST::Import*> import;
%type <CSSP::AST::VariableSetter*> variableSetter;
%type <CSSP::AST::Media*> media;

%type <CSSP::Token> string;

%locations

%%

// main
preprocesor
    : globalInstructions END {
        driver.setNodesAsCurrentTreeElement($1);
    }

// global instructions
globalInstructions
    : %empty {
        $$ = new std::vector<CSSP::AST::Node*>();
    }
    | globalInstructions globalInstruction {
        $1->push_back($2);
        $$ = $1;
    }

globalInstruction
    : block {
        $$ = $1;
    }
    | import {
        $$ = $1;
    }
    | media {
        $$ = $1;
    }
    | variableSetter {
        $$ = $1;
    }

// local instructions
instructions
    : %empty {
        $$ = new std::vector<CSSP::AST::Node*>();
    }
    | instructions instruction {
        $1->push_back($2);
        $$ = $1;
    }

instruction
    : block {
        $$ = $1;
    }
    | property {
        $$ = $1;
    }
    | variableSetter {
        $$ = $1;
    }

// import
import
    : IMPORT RAW_STRING SEMICOLON {
        driver.pushFileToQueue($2.toString());
        std::string path = driver.getRealPath($2.toString());
        $$ = new CSSP::AST::Import($2.toString(), path);
    }

// media
media
    : MEDIA mediaList LBRACE instructions RBRACE {
        $$ = new CSSP::AST::Media($2, $4);
    }

mediaList
    : %empty {
        $$ = new std::vector<CSSP::AST::Node*>();
    }
    | mediaList string {
        $1->push_back(new CSSP::AST::String($2.toString()));
        $$ = $1;
    }
    | mediaList LPAREN string COLON value RPAREN {
        $1->push_back(new CSSP::AST::MediaEntry($3.toString(), $5));
        $$ = $1;
    }

// variable (setter)
variableSetter
    : DOLLAR string COLON value SEMICOLON {
        $$ = new CSSP::AST::VariableSetter($2.toString(), $4);
    }

// block
block
    : selector LBRACE instructions RBRACE {
        $$ = new CSSP::AST::Block($1, $3);
    }

// selector
selector
    : selectorEntryType {
        $$ = new std::vector<CSSP::AST::Node*>();
        $$->push_back($1);
    }
    | selector selectorEntryType {
        $1->push_back($2);
        $$ = $1;
    }

selectorEntryType
    : selectorEntry {
        $$ = $1;
    }
    | selectorSeparator {
        $$ = $1;
    }

selectorSeparator
    : TILDE {
        $$ = (new CSSP::AST::Separator())->setToken($1);
    }
    | PLUS {
        $$ = (new CSSP::AST::Separator())->setToken($1);
    }
    | COMMA {
        $$ = (new CSSP::AST::Separator())->setToken($1);
    }
    | GT {
        $$ = (new CSSP::AST::Separator())->setToken($1);
    }
    | AMP {
        $$ = (new CSSP::AST::Separator())->setToken($1);
    }

selectorEntry
    : string {
        $$ = (new CSSP::AST::Selector(
            CSSP::AST::Selector::SelectorType::TAG,
            $1.toString()
        ))->setToken($1);
    }
    | valueVariable {
        $$ = (new CSSP::AST::Selector(
            CSSP::AST::Selector::SelectorType::TAG,
            "",
            nullptr,
            (CSSP::AST::Variable*) $1
        ))->setToken($1->getToken());
    }
    | DOT string {
        $$ = (new CSSP::AST::Selector(
            CSSP::AST::Selector::SelectorType::CLASS,
            $2.toString()
        ))->setToken($1);
    }
    | DOT valueVariable {
        $$ = (new CSSP::AST::Selector(
            CSSP::AST::Selector::SelectorType::CLASS,
            "",
            nullptr,
            (CSSP::AST::Variable*) $2
        ))->setToken($1);
    }
    | HASH string {
        $$ = (new CSSP::AST::Selector(
            CSSP::AST::Selector::SelectorType::ID,
            $2.toString()
        ))->setToken($1);
    }
    | HASH valueVariable {
        $$ = (new CSSP::AST::Selector(
            CSSP::AST::Selector::SelectorType::ID,
            "",
            nullptr,
            (CSSP::AST::Variable*) $2
        ))->setToken($1);
    }
    | COLON string {
        $$ = (new CSSP::AST::Selector(
            CSSP::AST::Selector::SelectorType::PSEUDOCLASS,
            $2.toString()
        ))->setToken($1);
    }
    | COLON COLON string {
        $$ = (new CSSP::AST::Selector(
            CSSP::AST::Selector::SelectorType::PSEUDOELEMENT,
            $3.toString()
        ))->setToken($1);
    }
    | LBRACKET string RBRACKET {
        $$ = (new CSSP::AST::Selector(
            CSSP::AST::Selector::SelectorType::ATTRIBUTE,
            $2.toString()
        ))->setToken($1);
    }
    | LBRACKET string EQUAL value RBRACKET {
        $$ = (new CSSP::AST::Selector(
            CSSP::AST::Selector::SelectorType::ATTRIBUTE,
            $2.toString(),
            $4
        ))->setToken($1);
    }

// property
property
    : string COLON valueList modifier SEMICOLON {
        $$ = new CSSP::AST::Property(
            (new CSSP::AST::String($1.toString()))->setToken($1),
            $3,
            $4
        );
    }

valueList
    : value {
        $$ = new std::vector<CSSP::AST::Node*>();
        $$->push_back($1);
    }
    | valueList COMMA value {
        $1->push_back((new CSSP::AST::Separator())->setToken($2));
        $1->push_back($3);
        $$ = $1;
    }
    | valueList value {
        $1->push_back($2);
        $$ = $1;
    }

modifier
    : %empty {
        $$ = new CSSP::AST::Modifier();
    }
    | BANG STRING {
        $$ = (new CSSP::AST::Modifier($2.toString()))->setToken($2);
    }

// value
value
    : valueVariable {
        $$ = $1;
    }
    | valueString {
        $$ = $1;
    }
    | valueCalculation {
        $$ = $1;
    }
    | valueColor {
        $$ = $1;
    }
    | valueNumber {
        $$ = $1;
    }

valueVariable
    : DOLLAR LBRACE string RBRACE {
        $$ = (new CSSP::AST::Variable($3.toString()))->setToken($1);
    }

valueString
    : RAW_STRING {
        $$ = (new CSSP::AST::String($1.toString()))->setToken($1);
    }
    | string {
        // string can be a number with unit string
        CSSP::AST::Value *value = nullptr;
        try {
            std::stoi($1.toString());
            value = new CSSP::AST::Number($1.toString());
        } catch(std::invalid_argument) {
            value = new CSSP::AST::String($1.toString());
        }
        $$ = value->setToken($1);
    }

valueNumber
    : NUMBER DOT string {
        $$ = (new CSSP::AST::Number($1.toString() + "." + $3.toString()))->setToken($1);
    }
    | string DOT string {
        // string can be a number with unit string
        CSSP::AST::Value *value = nullptr;
        try {
            std::stof($1.toString());
            value = new CSSP::AST::Number($1.toString() + "." + $3.toString());
        } catch(std::invalid_argument) {
            value = new CSSP::AST::String($1.toString() + "." + $3.toString());
        }
        $$ = (value)->setToken($1);
    }
    | NUMBER DOT NUMBER {
        $$ = (new CSSP::AST::Number($1.toString() + "." + $3.toString()))->setToken($1);
    }
    | DOT string {
        $$ = (new CSSP::AST::Number("0." + $2.toString()))->setToken($1);
    }
    | DOT NUMBER {
        $$ = (new CSSP::AST::Number("0" + $2.toString()))->setToken($1);
    }
    | DOT NUMBER PERCENT {
        $$ = (new CSSP::AST::Number("0." + $2.toString() + "%"))->setToken($1);
    }
    | NUMBER DOT NUMBER PERCENT {
        $$ = (new CSSP::AST::Number($1.toString() + "." + $3.toString() + "%"))->setToken($1);
    }
    | NUMBER {
        $$ = (new CSSP::AST::Number($1.toString()))->setToken($1);
    }

valueCalculation
    : LPAREN value PLUS value RPAREN {
        $$ = (new CSSP::AST::Calculation($2, $4, token::PLUS))->setToken($1);
    }
    | LPAREN value MINUS value RPAREN {
        $$ = (new CSSP::AST::Calculation($2, $4, token::MINUS))->setToken($1);
    }
    | LPAREN value ASTERISK value RPAREN {
        $$ = (new CSSP::AST::Calculation($2, $4, token::ASTERISK))->setToken($1);
    }
    | LPAREN value DIVIDE value RPAREN {
        $$ = (new CSSP::AST::Calculation($2, $4, token::DIVIDE))->setToken($1);
    }

valueColor
    : HASH HEX {
        $$ = (new CSSP::AST::Color($2.toString()))->setToken($1);
    }


//string helper
string
    : STRING {
        $$ = $1;
    }
    | HEX {
        $$ = $1;
    }

%%

void CSSP::Parser::error( const location_type &l, const std::string &err_message )
{
    // because &l is not valid
   std::cerr << "Error: " << err_message << " at " << this->lexer.getCurrentLocation() << "\n";
}
