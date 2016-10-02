#include <iostream>
#include <cstring>

#include "lib/logger/Logger.hpp"
#include "lib/driver/Driver.hpp"


void printHelp(std::string binary) {
    CSSP::Logger err(std::cerr, CSSP::Logger::colorRed);
    CSSP::Logger info(std::cerr, CSSP::Logger::colorDefault);

    err
        << "Driver error"
        << std::endl;

    info
        << "Usage: "
        << std::endl;

    info
        << binary
        << " -f <filename> - parse given file"
        << std::endl;

    info
        << binary
        << " -i            - parse standard input"
        << std::endl;

    return;
}

int processInput(int argc, const char *argv[]) {
    CSSP::Driver Driver;

    if (argc >= 2) {
        if (argc >= 3 && std::strncmp(argv[1], "-f", 2) == 0) {
            return Driver.parse(argv[2]);
        }
        if (std::strncmp(argv[1], "-i", 2) == 0) {
            return Driver.parse(std::cin);
        }
    }

    printHelp(argv[0]);
    return EXIT_FAILURE;
}

int main(const int argc, const char **argv) {
    int code = processInput(argc, argv);
    std::cout << CSSP::Logger::colorDefault << std::endl;

    return code;
}
