#include <iostream>
#include <cstring>

#include "lib/logger/Logger.hpp"
#include "lib/driver/Driver.hpp"


void printHelp(std::string binary) {
    CSSP::Logger err(std::cerr, CSSP::Logger::colorRed);

    err
        << "Driver error"
        << std::endl;

    std::cout
        << "Usage: "
        << std::endl;

    std::cout
        << binary
        << " -f <filename> - parse given file"
        << std::endl;

    std::cout
        << binary
        << " -i            - parse standard input"
        << std::endl;

    return;
}

int main(const int argc, const char **argv) {
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
