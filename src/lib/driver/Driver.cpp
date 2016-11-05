#include <cctype>
#include <fstream>

#include "lib/driver/Driver.hpp"

CSSP::Driver::~Driver() {
    delete (lexer);
    lexer = nullptr;

    delete (parser);
    parser = nullptr;
}

int CSSP::Driver::parse(const char *const filename) {
    if (filename == nullptr) {
        this->error
            << "Failed to read from file"
            << this->error.end()
            << std::endl;

        return EXIT_FAILURE;
    }

    std::ifstream in_file(filename);
    if (!in_file.good()) {
        this->error
            << "Failed to read from file"
            << this->error.end()
            << std::endl;

        return EXIT_FAILURE;
    }

    return parse_helper(in_file);
}

int CSSP::Driver::parse(std::istream &stream) {
    if (!stream.good() && stream.eof()) {
        this->error
            << "Failed to read from stream"
            << this->error.end()
            << std::endl;
        return EXIT_FAILURE;
    }

    return parse_helper(stream);
}


int CSSP::Driver::parse_helper(std::istream &stream) {

    delete (lexer);
    try {
        lexer = new CSSP::Lexer(&stream);
    }
    catch (std::bad_alloc &ba) {
        this->error
            << "Failed to allocate lexer: ("
            << ba.what()
            << ")"
            << this->error.end()
            << std::endl;

        exit(EXIT_FAILURE);
    }

    delete (parser);
    try {
        parser = new CSSP::Parser((*lexer),(*this));
    }
    catch (std::bad_alloc &ba) {
        this->error
            << "Failed to allocate parser: ("
            << ba.what()
            << ")"
            << this->error.end()
            << std::endl;

        exit(EXIT_FAILURE);
    }

    if (parser->parse() != EXIT_SUCCESS) {
        this->error
            << "Parser failed - parser end in non-acceptable state"
            << this->error.end()
            << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
