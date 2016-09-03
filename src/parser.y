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

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert
%define parse.error verbose

// typeless tokens
%token END_OF_FILE
%token NEW_LINE "\n"
%token COLON ":"
%token SEMICOLON ";"
%token COMMA ","
%token LPAREN "("
%token RPAREN ")"
%token LBRACKET "{"
%token RBRACKET "}"

%token IMPORT

// string tokens
// <std::string> selector tokens
%token <std::string> TAG;
%token <std::string> CLASS;
%token <std::string> ID;
%token <std::string> PSEUDO_CLASS;
%token <std::string> PSEUDO_ELEMENT;
%token <std::string> SELECTOR_SEPARATOR

%token <std::string> VARIABLE_NAME
%token <std::string> PROPERTY_NAME
%token <std::string> VALUE
%token <std::string> MODIFIER
%token <std::string> SELECTOR

%token <std::string> UNIT_VALUE;

%token               UPPER
%token               LOWER
%token <std::string> WORD
%token               CHAR

%locations

%%

preprocesor
    : program

program
    : %empty
    | program instruction

instruction
    : node

node
    : selector LBRACKET innerNode RBRACKET

selector
    : selectorNode
    | selector SELECTOR_SEPARATOR selectorNode
    | selector COMMA selectorNode
    | selector selectorNode

selectorNode
    : selectorEntry
    | selectorNode selectorEntry

selectorEntry
    : TAG
    | CLASS
    | ID
    | PSEUDO_CLASS
    | PSEUDO_ELEMENT

innerNode
    : %empty
    | innerNode node
    | innerNode property

property
    : property_name COLON property_value /*modifier*/ SEMICOLON

property_name
    : PROPERTY_NAME
    | TAG

property_value
    : property_value_entry
    | property_value property_value_entry


property_value_entry
    : TAG
    | PROPERTY_NAME
    // as color
    | ID
    | UNIT_VALUE

modifier
    : %empty
    | MODIFIER

%%

/*

list
  : item
  | list item
  ;

item
  : UPPER   { driver.add_upper(); }
  | LOWER   { driver.add_lower(); }
  | WORD    { driver.add_word( $1 ); }
  | NEW_LINE { driver.add_newline(); }
  | CHAR    { driver.add_char(); }
  ;
  */

void CSSP::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
