#include <iostream>
#include <fstream>

#include "Logger.hpp"

/**
 * Some constants
 */
const std::string CSSP::Logger::colorDefault = "\033[0m";
const std::string CSSP::Logger::colorBlack = "\033[1;30m";
const std::string CSSP::Logger::colorRed = "\033[1;31m";
const std::string CSSP::Logger::colorGreen = "\033[1;32m";
const std::string CSSP::Logger::colorYellow = "\033[1;33m";
const std::string CSSP::Logger::colorBlue = "\033[1;34m";
const std::string CSSP::Logger::colorMagenta = "\033[1;35m";
const std::string CSSP::Logger::colorCyan = "\033[1;36m";
const std::string CSSP::Logger::colorWhite = "\033[1;97m";

/**
 * Set logger output color
 * @param color
 */
void CSSP::Logger::setColor(std::string color) {
    this->color = color;
}

/**
 * Reset output color
 * @return default color
 */
std::string CSSP::Logger::end() {
    return Logger::colorDefault;
}
