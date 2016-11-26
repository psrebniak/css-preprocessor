#include <iostream>
#include <cstring>

#include "lib/logger/Logger.hpp"
#include "lib/driver/Driver.hpp"

void printHelp(std::string binary) {
    CSSP::Logger err(std::cerr, CSSP::Logger::colorRed);
    CSSP::Logger info(std::cerr, CSSP::Logger::colorDefault);

    err
        << "Driver error"
        << err.end()
        << std::endl;

    info
        << "Usage: "
        << err.end()
        << std::endl;

    info
        << binary
        << " -f <filename> - parse given file"
        << err.end()
        << std::endl;

    info
        << binary
        << " -i            - parse standard input"
        << err.end()
        << std::endl;

    return;
}

int main(int argc, const char *argv[]) {
    CSSP::Driver Driver;

    if (argc >= 2) {
        if (argc >= 3 && std::strncmp(argv[1], "-f", 2) == 0) {
            Driver.parse(argv[2]);
            return Driver.getGenerator()->generateOutput(std::cout);
        }
        if (std::strncmp(argv[1], "-i", 2) == 0) {
            Driver.parse(std::cin);
            return Driver.getGenerator()->generateOutput(std::cout);
        }
    }

    printHelp(argv[0]);
    return EXIT_FAILURE;
}
