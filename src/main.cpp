#include <iostream>
#include <cstring>

#include "lib/driver/Driver.hpp"

void printHelp(std::string binary) {
    std::cerr << "Driver error" << std::endl;
    std::cout << "Usage: " << std::endl;
    std::cout << binary << " -f <filename> - parse given file" << std::endl;
    std::cout << binary << " -i            - parse standard input" << std::endl;

    return;
}

int main(const int argc, const char **argv) {
    CSSP::Driver Driver;

    if (argc >= 2) {
        if (argc >= 3 && std::strncmp( argv[1], "-f", 2 ) == 0) {
            return Driver.parse(argv[2]);
        }
        if (std::strncmp( argv[1], "-i", 2 ) == 0) {
            return Driver.parse(std::cin);
        }
    }

    printHelp(argv[0]);
    return EXIT_FAILURE;
}
