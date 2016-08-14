#include <iostream>
#include <cstring>

#include "lib/driver/Driver.hpp"

int main(const int argc, const char **argv) {
    CSSP::Driver Driver;
    Driver.parse(std::cin);

    return (EXIT_SUCCESS);
}
