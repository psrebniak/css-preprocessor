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
%token <std::string> RAW_STRING

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
    | LPAREN STRING COLON property_value_entry RPAREN

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
        driver.log << "TagName: " << $1 << std::endl;
    }
    | DOT STRING {
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
    | innerNode property

property
    : STRING COLON property_value modifier SEMICOLON
    | STRING COLON property_value modifier

property_value
    : property_value_entry
    | property_value COMMA property_value_entry
    | property_value property_value_entry

property_value_entry
    : STRING LPAREN property_value RPAREN {
        driver.log << "Property-value: " << $1 << "(" << "VALUE" << ")" << std::endl;
    }
    | DOLLAR STRING {
        driver.log << "Variable: " << $2 << std::endl;
    }
    | HASH LBRACE DOLLAR STRING RBRACE {
        driver.log << "Variable: " << $4 << std::endl;
    }
    | STRING {
        driver.log << "Property-value: " << $1 << std::endl;
    }
    | RAW_STRING {
        driver.log << "Property-value: " << $1 << std::endl;
    }
    | NUMBER DOT NUMBER PERCENT {
            driver.log << "Property-value: DOT " << $1 << "." << $3 << "%" << std::endl;
    }
    | NUMBER DOT NUMBER {
                driver.log << "Property-value: DOT " << $1 << "." << $3 << std::endl;
    }
    | DOT NUMBER PERCENT {
        driver.log << "Property-value: DOT " << $2 << std::endl;
    }
    | DOT NUMBER {
            driver.log << "Property-value: DOT " << $2 << std::endl;
    }
    | DOT STRING {
        driver.log << "Property-value: DOT " << $2 << std::endl;
    }
    | HASH HEX {
        driver.log << "Property-value: HEX " << $2 << std::endl;
    }
    | HASH NUMBER {
        driver.log << "Property-value: HEX " << $2 << std::endl;
    }
    | NUMBER PERCENT {
        driver.log << "Property-value: " << $1 << "PERCENT" << std::endl;
    }
    | NUMBER {
        driver.log << "Property-value: " << $1 << std::endl;
    }


modifier
    : %empty
    | BANG STRING {
        driver.log << "Modifier: " << $2 << std::endl;
    }

%%

void CSSP::Parser::error(const location_type &l, const std::string &err_message)
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
