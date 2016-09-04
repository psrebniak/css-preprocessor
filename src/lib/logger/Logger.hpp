#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <ostream>

namespace CSSP {

    class Logger {
    public:
        Logger(std::ostream &os) :
            os_(os) {}

        Logger(std::ostream &os, std::string color) :
            os_(os),
            color(color) {}

        static const std::string colorDefault;
        static const std::string colorBlack;
        static const std::string colorRed;
        static const std::string colorGreen;
        static const std::string colorYellow;
        static const std::string colorBlue;
        static const std::string colorMagenta;
        static const std::string colorCyan;
        static const std::string colorWhite;

    private:
        std::string color = colorDefault;

        template<typename T>
        friend std::ostream &operator<<(Logger &log, T op) {
            log.os_ << log.color << op << Logger::colorDefault;
            return log.os_;
        }

        std::ostream &os_;
    };
}

#endif
