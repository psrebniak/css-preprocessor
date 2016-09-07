%skeleton "lalr1.cc"
%debug
%defines
%define api.namespace {CSSP}
%define parser_class_name {Parser}

%code requires {
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
%token <std::string> HEX
%token <std::string> STRING
%token <std::string> NUMBER
%token <std::string> CHAR

// typeless tokens
%token END_OF_FILE
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

%locations

%%

preprocesor
    : program {
        driver.log << "process complete" << std::endl;
    }

program
    : %empty
    | program instruction

instruction
    : node

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

selectorEntry
    : STRING {
        driver.log << "TagName: " << $1 << std::endl;
    }
    | DOT STRING {
        driver.log << "Class: " << $2 << std::endl;
    }
    | HASH STRING {
        driver.log << "Id: " << $2 << std::endl;
    }
    | COLON STRING {
        driver.log << "PseudoClass: " << $2 << std::endl;
    }
    | COLON COLON STRING {
        driver.log << "PseudoElement: " << $3 << std::endl;
    }

innerNode
    : %empty
    | innerNode node
    | innerNode property

property
    : STRING COLON property_value modifier SEMICOLON

property_value
    : property_value_entry
    | property_value property_value_entry

property_value_entry
    : STRING
    | HASH HEX
    | NUMBER

modifier
    : %empty
    | BANG STRING

%%

void CSSP::Parser::error(const location_type &l, const std::string &err_message)
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
