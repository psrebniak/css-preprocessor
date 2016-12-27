//
// Created by piotrek on 14.11.16.
//

#ifndef CSSPREPROCESSOR_GENERATOR_HPP
#define CSSPREPROCESSOR_GENERATOR_HPP

#include <utility>
#include <map>
#include <list>
#include <stack>
#include <fstream>
#include <src/lib/logger/Logger.hpp>

#include "lib/ast/value/value/Value.hpp"
#include "lib/types.hpp"
#include "lib/ast/node/Node.hpp"

namespace CSSP {
    class Generator {
    public:
        /**
         * Create new generator
         * @param fileToTreeMap - map created by driver
         * @param mainFile - main file (key in tree)
         * @param minify - should be output minified
         */
        Generator(FileToTreeMapType *fileToTreeMap, std::string mainFile, bool minify = false,
                  unsigned int stackSize = 16)
            : fileToTreeMap(*fileToTreeMap),
              error(std::cerr, Logger::colorRed),
              minify(minify),
              MAX_STACK_SIZE(stackSize) {
            this->pushFile(mainFile);
        }

        /**
         * Generate output to given stream
         * @param ostream
         * @return 0 if success, error code when error occured
         */
        int generateOutput(std::ostream &ostream);

        /**
         * push new file to stack top
         * @param filename map key
         * @return error code
         */
        bool pushFile(const std::string filename);

        /**
         * Register new error with given description
         * Error is write to this->error output
         * @param description
         */
        void registerError(const std::string description);

        /**
         * Register new variable or update already defined
         * @param name
         * @param value
         * @return
         */
        bool setVariable(const std::string name, CSSP::AST::Value *value);

        /**
         * Get variable with given name if exist, return null if not exist
         * @param name
         * @return variable or null
         */
        const CSSP::AST::Value *getVariable(std::string name);

        /**
         * Unset variable if exist
         * @param name
         * @return
         */
        bool unsetVariable(const std::string name);

        /**
         * Push selector list for current block
         * @param selectorList
         */
        void pushBlockSelector(std::list<std::string> *selectorList);

        /**
         * pop selector list for current block
         */
        void popBlockSelector();

        /**
         * Get latest block selector list or null if there is no lists on the stack
         * @return list<std::string> or null
         */
        std::list<std::string> *getLatestBlockSelector();

        /**
         * return string representing indentation
         * @return
         */
        const std::string getIndent() const;

        /**
         * get string with end of line character
         * @return
         */
        const std::string getEol() const;

        /**
         * true if output should be minified
         * @return
         */
        const bool isMinified() const;

    protected:
        /**
         * Map passed with constructor
         */
        FileToTreeMapType fileToTreeMap;

        /**
         * Stack for files to proceed
         */
        std::stack<std::pair<NodeListType::const_iterator, NodeListType *> > stack;

        /**
         * Calculated selectors for external blocks (used inside blocks)
         */
        std::stack<std::list<std::string> *> blockSelectors;

        /**
         * map of variables
         */
        NameToVariableMapType variableMap;

        /**
         * should be output minified
         */
        const bool minify;

        /**
         * max number of files in stack
         */
        const int MAX_STACK_SIZE = 16;

        /**
         * logger output
         */
        Logger error;
    };
}

#endif //CSSPREPROCESSOR_GENERATOR_HPP
