#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__

#include <string>
#include <cstddef>
#include <istream>
#include <iostream>
#include <utility>
#include <map>
#include <queue>

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
        /**
         * Create new Driver
         * @param os info/warning output stream
         */
        Driver(std::ostream &os) :
            log(os, Logger::colorCyan),
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

        /**
         * Create new generator with current fileToFreeMap
         * @param minify should be output minified
         * @return new Generator instance
         */
        CSSP::Generator *getGenerator(bool minify = false);

        /**
         * Get access to fileToTreeMap
         * @return fileToTreeMap
         */
        const FileToTreeMapType *getFileToTreeMap() const;

    protected:
        /**
         * helper method, parse given stream
         * @param stream
         * @return
         */
        int parseHelper(std::istream &stream);

        /**
         * return true if file is already parsed
         * @param filename
         * @return
         */
        bool isFileInTree(std::string filename);

        /**
         * main file directory name or current working directory in stream parse case
         */
        std::string directory;

        /**
         * main file realpath
         */
        std::string mainFileName;

        /**
         * current processed filename
         */
        std::string currentFileName;

        /**
         * file to process queue
         */
        std::queue<std::string> fileQueue;

        /**
         * realpath to tree map
         */
        FileToTreeMapType fileToTreeMap;

        /**
         * warning logger
         */
        Logger log;

        /**
         * error logger
         */
        Logger error;

        /**
         * Parser instance
         */
        CSSP::Parser *parser = nullptr;

        /**
         * Lexer instance
         */
        CSSP::Lexer *lexer = nullptr;

        /**
         * get realpath of given file (as cwd is used directory parameter)
         * @param path
         * @return
         */
        std::string getRealPath(std::string path);

        /**
         * run queue and proceed used files
         * @return
         */
        int processQueue();

        /**
         * run queue and use DebugString method instead of generate
         * @return
         */
        int debugQueue();

        /**
         * Parse partial with given filename
         * @return
         */
        int parsePartial(std::string);

        /**
         * Push new file to queue
         * @param filename
         */
        void pushFileToQueue(std::string filename);

        /**
         * Set tree for currently parsed element (used by lexer)
         * @param nodes
         */
        void setNodesAsCurrentTreeElement(NodeListType *nodes);
    };
}
#endif
