# CSSP - CSS preprocessor library

[![Build Status](https://travis-ci.com/psrebniak/css-preprocessor.svg?token=qij5pjXxGBUqQ2D9ycyK&branch=master)](https://travis-ci.com/psrebniak/css-preprocessor)

**WARNING**<br/>
**this library is abandoned and no longer maintained**

## What's this
This library is CSS preprocessor built on LALR(1) grammar. 
It uses Flex (The Fast Lexical Analyzer) and Bison(Yacc-compatible Parser Generator) to handle grammar. It is written in C++11. 

CSS grammar has few traps, including significant white spaces and multiple rules with ":" character that cannot be easy handled on parser with single lookahead. 
For this reason LALR(1) parser is not good choice to handle CSS grammar, but main goal of this library is achieve high parsing speed and it is achieved. 

This library can be an example how to build medium size application with flex and bison.

## Compilation
```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ ctest .
```

## Grammar
See `tests` directory. 

## License
MIT
