#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__

#include <string>
#include <cstddef>
#include <istream>
#include <iostream>

#include "lib/lexer/Lexer.hpp"
#include "lib/logger/Logger.hpp"
#include "generated/parser.hpp"

namespace CSSP {

    class Driver {
    public:
        Driver() :
            log(std::cout, Logger::blueColor),
            warn(std::cout, Logger::yellowColor),
            error(std::cerr, Logger::redColor) {}

        virtual ~Driver();

        /**
         * parse - parse from a file
         * @param filename - valid string with input file
         */
        int parse(const char *const filename);

        /**
         * parse - parse from a c++ input stream
         * @param is - std::istream&, valid input stream
         */
        int parse(std::istream &iss);

        Logger log;
        Logger warn;
        Logger error;
    private:

        int parse_helper(std::istream &stream);

        CSSP::Parser *parser = nullptr;
        CSSP::Scanner *scanner = nullptr;
    };

}
#endif
