%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace {CSSP}
%define parser_class_name {Parser}

%code requires {
   #include <map>
   #include <vector>
   #include "lib/ast/Ast.hpp"
   #include "lib/token/Token.hpp"

   namespace CSSP {
      class Driver;
      class Scanner;
   }
}

%parse-param { Scanner  &scanner  }
%parse-param { Driver  &driver  }

%code {
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   /* include for all driver functions */
   #include "lib/driver/Driver.hpp"
   #include "lib/logger/Logger.hpp"


#undef yylex
#define yylex scanner.yylex
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


// typeless tokens
%token END          0       "End of file"
%token NEW_LINE     "\n"
%token SPACE        " "
%token TAB          "\t"

%token TILDE        "~"
%token BANG         "!"
%token AT           "@"
%token HASH         "#"
%token DOLLAR       "$"
%token PERCENT      "%"
%token CARET        "^"
%token AMP          "&"
%token ASTERISK     "*"
%token LPAREN       "("
%token RPAREN       ")"
%token MINUS        "-"
%token UNDERSCORE   "_"
%token PLUS         "+"
%token EQUAL        "="

%token LBRACKET     "["
%token RBRACKET     "]"
%token LBRACE       "{"
%token RBRACE       "}"

%token COLON        ":"
%token SEMICOLON    ";"
%token COMMA        ","
%token DOT          "."
%token LT           "<"
%token GT           ">"
%token QUESTION     "?"
%token DIVIDE       "/"


%type <CSSP::AST::Node*> modifier;


%type <CSSP::AST::Value*> value;
%type <CSSP::AST::Value*> value_variable;
%type <CSSP::AST::Value*> value_string;
%type <CSSP::AST::Value*> value_number;
%type <CSSP::AST::Value*> value_calculation;
%type <CSSP::AST::Value*> value_color;

%locations

%%

preprocesor
    : program END {
        driver.log << "process complete" << std::endl;
    }

program
    : %empty
    | program instruction

instruction
    : node
    | variable
    | query

query
    : AT STRING queryNode LBRACE innerNode RBRACE
    | AT STRING RAW_STRING SEMICOLON
    | AT STRING STRING SEMICOLON
    | AT STRING STRING LPAREN RPAREN SEMICOLON
    | AT STRING STRING LPAREN property_value RPAREN SEMICOLON

queryNode
    : queryEntry
    | queryNode queryEntry

queryEntry
    : STRING
    | LPAREN STRING COLON value RPAREN

variable:
    DOLLAR STRING COLON property_value modifier SEMICOLON {
        driver.log << "Dollar: " << $2.toString() << " : " << "value" << std::endl;
    }

node
    : selector LBRACE innerNode RBRACE

selector
    : selectorNode
    | selector selectorSeparator selectorNode
    | selector selectorNode

selectorNode
    : selectorEntry
    | selectorNode selectorEntry

selectorSeparator
    : TILDE
    | PLUS
    | COMMA
    | GT
    | AMP

selectorEntry
    : STRING {
        driver.log << "TagName: " << $1.toString() << std::endl;
    }
    | DOT STRING {
        driver.log << "Class: " << $2.toString() << std::endl;
    }
    | HASH LBRACE DOLLAR STRING RBRACE {
        driver.log << "Variable: " << $4.toString() << std::endl;
    }
    | HASH STRING {
        driver.log << "Id: " << $2.toString() << std::endl;
    }
    | COLON STRING LPAREN selectorEntry RPAREN {
        driver.log << "PseudoClass: " << $2.toString() << std::endl;
    }
    | COLON STRING {
        driver.log << "PseudoClass: " << $2.toString() << std::endl;
    }
    | COLON COLON STRING {
        driver.log << "PseudoElement: " << $3.toString() << std::endl;
    }
    | LBRACKET STRING RBRACKET {
        driver.log << "Attribute: " << $2.toString() << std::endl;
    }
    | LBRACKET STRING EQUAL RAW_STRING RBRACKET {
        driver.log << "Attribute: " << $2.toString() << " AS " << $4.toString() << std::endl;
    }

innerNode
    : %empty
    | innerNode variable
    | innerNode query
    | innerNode node
    | innerNode property {
        //driver.log << $2->toString() << driver.log.end() << std::endl;
    }

property
    : STRING COLON property_value modifier SEMICOLON {
        // $$ = new CSSP::AST::Property(new CSSP::AST::String($1), $3, $4);
    }
    | STRING COLON property_value modifier {
        // $$ = new CSSP::AST::Property(new CSSP::AST::String($1), $3, $4);
    }

property_value
    : value
    | property_value COMMA value
    | property_value value

modifier
    : %empty {
        $$ = new CSSP::AST::Modifier();
    }
    | BANG STRING {
        $$ = (new CSSP::AST::Modifier($2.toString()))->setToken($2);
    }

value
    : value_variable {
        driver.log << "VARIABLE: " << $1->toString() << driver.log.end() << std::endl;
        $$ = $1;
    }
    | value_string {
        driver.log << "STRING: " << $1->toString() << driver.log.end() << std::endl;
        $$ = $1;
    }
    | value_calculation {
        driver.log << "CALCULTION: " << $1->toString() << driver.log.end() << std::endl;
        $$ = $1;
    }
    | value_color {
        driver.log << "COLOR: " << $1->toString() << driver.log.end() << std::endl;
        $$ = $1;
    }
    | value_number {
        driver.log << "NUMBER: " << $1->toString() << driver.log.end() << std::endl;
        $$ = $1;
    }

value_variable
    : DOLLAR STRING {
        $$ = new CSSP::AST::Variable($2.toString());
        ///@todo set token as $
    }
    | HASH LBRACE DOLLAR STRING RBRACE {
        $$ = new CSSP::AST::Variable($4.toString());
        ///@todo set token as #
    }

value_string
    : RAW_STRING {
        $$ = (new CSSP::AST::String($1.toString()))->setToken($1);
    }
    | STRING {
        // string can be a number with unit string
        CSSP::AST::Value *value = NULL;
        try {
            std::stoi($1.toString());
            value = new CSSP::AST::Number($1.toString());
        } catch(std::invalid_argument) {
            value = new CSSP::AST::String($1.toString());
        }
        $$ = value->setToken($1);
    }

value_number
    : NUMBER DOT STRING {
        $$ = (new CSSP::AST::Number($1.toString() + "." + $3.toString()))->setToken($1);
    }
    | NUMBER DOT NUMBER {
        $$ = (new CSSP::AST::Number($1.toString() + "." + $3.toString()))->setToken($1);
    }
    | DOT STRING {
        $$ = new CSSP::AST::Number("0." + $2.toString());
    }
    | DOT NUMBER {
        $$ = new CSSP::AST::Number("0" + $2.toString());
    }
    | DOT NUMBER PERCENT {
        $$ = new CSSP::AST::Number("0." + $2.toString() + "%");
    }
    | NUMBER DOT NUMBER PERCENT {
        $$ = (new CSSP::AST::Number($1.toString() + "." + $3.toString() + "%"))->setToken($1);
    }
    | NUMBER {
        $$ = (new CSSP::AST::Number($1.toString()))->setToken($1);
    }

value_calculation
    : LPAREN value PLUS value RPAREN {
        $$ = new CSSP::AST::Calculation($2, $4, token::PLUS);
    }
    | LPAREN value MINUS value RPAREN {
        $$ = new CSSP::AST::Calculation($2, $4, token::MINUS);
    }
    | LPAREN value ASTERISK value RPAREN {
        $$ = new CSSP::AST::Calculation($2, $4, token::ASTERISK);
    }
    | LPAREN value DIVIDE value RPAREN {
        $$ = new CSSP::AST::Calculation($2, $4, token::DIVIDE);
    }

value_color
    : HASH NUMBER {
        $$ = new CSSP::AST::Color($2.toString());
    }
    | HASH HEX {
        $$ = new CSSP::AST::Color($2.toString());
    }

%%

void CSSP::Parser::error(const location_type &l, const std::string &err_message)
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
