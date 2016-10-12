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
%token <std::string> RAW_STRING

%token <std::string> HEX
%token <std::string> STRING
%token <std::string> NUMBER
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
        driver.log << "Dollar: " << $2 << " : " << "value" << std::endl;
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
        if (driver.scanner->lexerVirtualWhiteSpaceDetected) {
            driver.log << "Driver detect whitespace flag" << std::endl;
            driver.scanner->lexerVirtualWhiteSpaceDetected = 0;
        }
        driver.log << "TagName: " << $1 << std::endl;
    }
    | DOT STRING {
        if (driver.scanner->lexerVirtualWhiteSpaceDetected) {
            driver.log << "Driver detect whitespace flag";
            driver.scanner->lexerVirtualWhiteSpaceDetected = 0;
        }
        driver.log << "Class: " << $2 << std::endl;
    }
    | HASH LBRACE DOLLAR STRING RBRACE {
        driver.log << "Variable: " << $4 << std::endl;
    }
    | HASH STRING {
        driver.log << "Id: " << $2 << std::endl;
    }
    | COLON STRING LPAREN selectorEntry RPAREN {
        driver.log << "PseudoClass: " << $2 << std::endl;
    }
    | COLON STRING {
        driver.log << "PseudoClass: " << $2 << std::endl;
    }
    | COLON COLON STRING {
        driver.log << "PseudoElement: " << $3 << std::endl;
    }
    | LBRACKET STRING RBRACKET {
        driver.log << "Attribute: " << $2 << std::endl;
    }
    | LBRACKET STRING EQUAL RAW_STRING RBRACKET {
        driver.log << "Attribute: " << $2 << " AS " << $4 << std::endl;
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
        $$ = new CSSP::AST::Modifier($2);
    }

value
    : value_variable {
        $$ = $1;
    }
    | value_string {
        $$ = $1;
    }
    | value_calculation {
        $$ = $1;
    }
    | value_color {
        $$ = $1;
    }
    | value_number {
        $$ = $1;
    }

value_variable
    : DOLLAR STRING {
        $$ = new CSSP::AST::Variable($2);
    }
    | HASH LBRACE DOLLAR STRING RBRACE {
        $$ = new CSSP::AST::Variable($4);
    }

value_string
    : RAW_STRING {
        $$ = new CSSP::AST::String($1);
    }
    | STRING {

       /*
       if (std::stoi($1) > 0) {
            $$ = new CSSP::AST::Number($1);
        } else {
            $$ = new CSSP::AST::String($1);
        }
        */
    }

value_number
    : NUMBER DOT STRING {
        $$ = new CSSP::AST::Number($1, $3);
    }
    | NUMBER DOT NUMBER {
        $$ = new CSSP::AST::Number($1, $3);
    }
    | DOT STRING {
        $$ = new CSSP::AST::Number(0, $2);
    }
    | DOT NUMBER {
        $$ = new CSSP::AST::Number(0, $2);
    }
    | DOT NUMBER PERCENT {
        $$ = new CSSP::AST::Number(0, $2 + "%");
    }
    | NUMBER DOT NUMBER PERCENT {
        $$ = new CSSP::AST::Number($1, $3 + "%");
    }
    | NUMBER {
        $$ = new CSSP::AST::Number($1, "");
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
    : HEX NUMBER {
        $$ = new CSSP::AST::Color($2);
    }
    | HEX STRING {
        $$ = new CSSP::AST::Color($2);
    }

%%

void CSSP::Parser::error(const location_type &l, const std::string &err_message)
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
