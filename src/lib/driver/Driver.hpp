#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__

#include <string>
#include <cstddef>
#include <istream>
#include <iostream>
#include <utility>
#include <map>
#include <vector>

#include "lib/types.hpp"
#include "lib/lexer/Lexer.hpp"
#include "lib/logger/Logger.hpp"
#include "lib/ast/node/Node.hpp"
#include "lib/generator/Generator.hpp"
#include "generated/parser.hpp"

namespace CSSP {
    class Driver {
        friend class Parser;

    public:
        Driver() :
            log(std::cout, Logger::colorCyan),
            warn(std::cout, Logger::colorYellow),
            error(std::cerr, Logger::colorRed) {}

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

        CSSP::Generator *getGenerator();

        Logger log;
        Logger warn;
        Logger error;

    protected:
        int parse_helper(std::istream &stream);

        bool isFileInTree(std::string filename);

        std::string baseName;
        std::string mainFileName;
        std::string currentFileName;
        std::vector<std::string> fileQueue;
        FileToTreeMapType fileToTreeMap;

        CSSP::Parser *parser = nullptr;
        CSSP::Lexer *lexer = nullptr;

        int processQueue();

        int debugQueue();

        int parsePartial(std::string);

        void pushFileToQueue(std::string filename);

        void setNodesAsCurrentTreeElement(NodeVectorType *nodes);
    };
}
#endif
