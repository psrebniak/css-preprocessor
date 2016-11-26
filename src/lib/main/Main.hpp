//
// Created by piotrek on 26.11.16.
//

#ifndef CSSPREPROCESSOR_MAIN_HPP
#define CSSPREPROCESSOR_MAIN_HPP

#include <string>

namespace CSSP {

    /**
     * Main CLI application class
     */
    class Main {
    public:
        Main(int argc, char *argv[]) {
            this->parseOpt(argc, argv);
        }

        void parseOpt(int argc, char *argv[]);

        void help();

        int run();

    protected:
        /**
         * should loggers print anything
         */
        bool verbose = false;

        /**
         * minify code, use only for production purposes
         */
        bool minify = false;

        /**
         * should app print help and quit
         */
        bool printHelp = false;

        /**
         * indicate that getopt notice erorrs
         */
        bool hasError = false;

        /**
         * should parse stdin
         */
        bool readStdin = false;

        /**
         * should parse file from filename member
         */
        bool readFile = false;

        /**
         * filename for main file
         */
        std::string filename = std::string();
    };
}

#endif //CSSPREPROCESSOR_MAIN_HPP
