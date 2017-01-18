#include <string>
#include <cctype>
#include <fstream>
#include <unistd.h>
#include <string.h>

#include "lib/driver/Driver.hpp"

CSSP::Driver::~Driver() {

    for(const auto pair : this->fileToTreeMap) {
        while(!pair.second->empty()) {
            delete pair.second->front();
            pair.second->pop_front();
        }
        delete pair.second;
    }
    this->fileToTreeMap.clear();

    if (this->lexer) {
        delete this->lexer;
    }
    if (this->parser) {
        delete this->parser;
    }
}

int CSSP::Driver::parse(const char *const filename) {

    if (filename == nullptr) {
        this->error
            << "Failed to read from file"
            << this->error.end()
            << std::endl;

        return EXIT_FAILURE;
    }

    std::string path = this->getRealPath(filename);

    std::string name = basename(path.c_str());
    std::string dir = path.substr(0, path.length() - name.length());

    if (chdir(dir.c_str())) {
        this->error
            << "Failed to change directory relative to main file: "
            << dir
            << this->error.end()
            << std::endl;
        return EXIT_FAILURE;
    }

    this->directory = dir;
    this->mainFileName = path;
    this->pushFileToQueue(path);

    this->processQueue();

    return 0;
}

int CSSP::Driver::parse(std::istream &stream) {
    if (!stream.good() && stream.eof()) {
        this->error
            << "Failed to read from stream"
            << this->error.end()
            << std::endl;
        return EXIT_FAILURE;
    }

    char temp[256];
    getcwd(temp, 256);
    this->directory = std::string(temp);
    this->mainFileName = "STDIN";
    this->currentFileName = "STDIN";
    this->parseHelper(stream);

    this->processQueue();

    return 0;
}

int CSSP::Driver::parsePartial(const std::string filename) {
    std::ifstream file(filename);
    if (!file.good()) {
        this->error
            << "Failed to read from file: "
            << filename
            << this->error.end()
            << std::endl;

        return EXIT_FAILURE;
    }

    return this->parseHelper(file);
}

int CSSP::Driver::parseHelper(std::istream &stream) {

    if (this->lexer != nullptr) {
        delete this->lexer;
    }
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

    if (this->parser != nullptr) {
        delete this->parser;
    }
    try {
        parser = new CSSP::Parser((*lexer), (*this));
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

bool CSSP::Driver::isFileInTree(std::string filename) {
    FileToTreeMapType::const_iterator position;
    position = this->fileToTreeMap.find(filename);

    return position != this->fileToTreeMap.end();
}

void CSSP::Driver::pushFileToQueue(std::string filename) {
    if (access(filename.c_str(), F_OK) != 0) {
        this->error << "Cannot open file " << filename << this->error.end() << std::endl;
        return;
    }

    std::string path = this->getRealPath(filename);

    this->log
        << "Add file "
        << path
        << " into queue"
        << this->log.end()
        << std::endl;

    this->fileQueue.push(path);
}

int CSSP::Driver::processQueue() {

    while (!this->fileQueue.empty()) {
        std::string filename = this->fileQueue.front();
        if (!this->isFileInTree(filename)) {
            this->log
                << "Parse file: "
                << filename
                << this->log.end()
                << std::endl;

            this->currentFileName = filename;
            this->parsePartial(filename);
        } else {
            this->log
                << "File: "
                << filename
                << " already in tree"
                << this->log.end()
                << std::endl;
        }
        this->fileQueue.pop();
    }

    return 0;
}

void CSSP::Driver::setNodesAsCurrentTreeElement(NodeListType *nodes) {
    this->fileToTreeMap.insert(FileToTreePairType(
        this->currentFileName,
        nodes
    ));
}

int CSSP::Driver::debugQueue() {
    this->log
        << "Debug queue"
        << this->log.end()
        << std::endl;

    for (FileToTreeMapType::const_iterator i = this->fileToTreeMap.begin(); i != fileToTreeMap.end(); i++) {
        this->log
            << "File: "
            << i->first
            << this->log.end()
            << std::endl;

        NodeListType nodes = *i->second;

        for (auto const node : nodes) {
            this->log
                << node->debugString()
                << this->log.end()
                << std::endl;
        }
    }
    this->log
        << "End queue"
        << this->log.end()
        << std::endl;

    return 0;
}

CSSP::Generator *CSSP::Driver::getGenerator(bool minify) {
    return new CSSP::Generator(
        &this->fileToTreeMap,
        this->mainFileName,
        minify
    );
}

std::string CSSP::Driver::getRealPath(std::string path) {
    if (access(path.c_str(), F_OK) != 0) {
        this->error << "Cannot open file " << path << this->error.end() << std::endl;
        return std::string();
    }

    char *buffer = realpath(path.c_str(), nullptr);
    std::string realPath = std::string(buffer);
    delete buffer;

    return realPath;
}

const FileToTreeMapType *CSSP::Driver::getFileToTreeMap() const {
    return &(this->fileToTreeMap);
}
