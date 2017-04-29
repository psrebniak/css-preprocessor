# CSSP - CSS preprocessor library [![Build Status](https://travis-ci.org/psrebniak/css-preprocessor.svg?branch=master)](https://travis-ci.org/psrebniak/css-preprocessor)

**WARNING**<br/>
**this library is abandoned**

## What's this
This library is CSS preprocessor built on LALR(1) grammar. 
It uses Flex (The Fast Lexical Analyzer) and Bison (Yacc-compatible Parser Generator) to handle grammar. 
It is written in C++11. 

CSS grammar has few traps, including significant white spaces and multiple rules with ":" character that cannot be easy handled on parser with single lookahead. 
For this reasons LALR(1) parser is not good choice to handle CSS grammar, 
Main goal of this library was achieve high parsing speed, this justify parser choice. 

## Compilation
```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ ctest .
```

## Features

* block nesting with parent operator and handling multiple selectors with comma separator
* import files
* variables
* calculations
* for loop
* built-in minification (opt-in)

## Grammar
See `tests` directory. 

## Tests
* simple - file should be parsed without error
* in/out - parse in file and check output is matching out file
* valgrind - import all tests and check for memory leaks

## License
MIT
