//
// Created by piotrek on 26.11.16.
//

#include <iostream>
#include <cstring>
#include <getopt.h>
#include <zconf.h>

#include "lib/logger/Logger.hpp"
#include "lib/driver/Driver.hpp"
#include "Main.hpp"


/**
 * parse options and set proper members
 *
 * @param argc application argc param
 * @param argv application argv param
 */
void CSSP::Main::parseOpt(int argc, char *argv[]) {

    const struct option longopts[] =
        {
            {"help",     no_argument,       0, 'h'},
            {"verbose",  no_argument,       0, 'v'},
            {"minify",   no_argument,       0, 'm'},
            {"stdin",    no_argument,       0, 'i'},
            {"filename", required_argument, 0, 'f'},
            {0, 0,                          0, 0}
        };

    int index;
    int iarg = 0;

    opterr = 1;

    while (iarg != -1) {
        iarg = getopt_long(argc, argv, "hvmif:", longopts, &index);

        switch (iarg) {
            case 'h':
                this->printHelp = true;
                break;
            case 'v':
                this->verbose = true;
                break;
            case 'm':
                this->minify = true;
                break;
            case 'i':
                this->readStdin = true;
                break;
            case 'f':
                this->filename = optarg;
                this->readFile = true;
                break;
        }
    }
    if (!this->readStdin && !this->readFile) {
        this->printHelp = true;
    } else if (!(this->readStdin ^ this->readFile)) {
        std::cerr << "Error: Please use --file or --stdin option" << std::endl;
        this->hasError = true;
    }
    if (this->readFile) {
        if (access(this->filename.c_str(), F_OK) != 0) {
            std::cerr << "Error: Cannot get file access" << std::endl;
            this->hasError = true;
        }
    }
}

/**
 * print help
 */
void CSSP::Main::help() {
    std::cerr << "CSSP - CSS preprocessor" << std::endl;
    std::cerr << "Author: Piotr Srebniak, W-11, Wrocław Institute of Technology" << std::endl;
    std::cerr << std::endl;
    std::cerr << "-h --help               print help" << std::endl;
    std::cerr << "-v --verbose            print verbose information" << std::endl;
    std::cerr << "-m --minify             minify output" << std::endl;
    std::cerr << "-f --file <filename>    parse given file" << std::endl;
    std::cerr << "-i --stdin              parse standard input" << std::endl;
    std::cerr << std::endl;
}

/**
 * run driver
 * @return exit code
 */
int CSSP::Main::run() {
    // create stream to null device
    std::ostream *loggerStream = new std::ostream(0);

    // on verbose mode, use std::cerr as logger output
    if (this->verbose) {
        delete loggerStream;
        loggerStream = &std::cerr;
    }

    // print help if necessary
    if (this->hasError) {
        std::cerr << std::endl;
    }
    if (this->printHelp || this->hasError) {
        this->help();
        return 1;
    }

//     create new driver with prepared logger
    CSSP::Driver Driver(*loggerStream);
    if (this->readFile) {
        Driver.parse(this->filename.c_str());
    } else {
        Driver.parse(std::cin);
    }
    // return generator exit code
    auto exitCode = Driver.getGenerator(this->minify)->generateOutput(std::cout);

    if (!this->verbose) {
        delete loggerStream;
    }

    return exitCode;
}
