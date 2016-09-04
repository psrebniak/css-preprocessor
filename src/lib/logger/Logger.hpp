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

        static const std::string redColor;
        static const std::string yellowColor;
        static const std::string blueColor;
        static const std::string defaultColor;
    private:
        std::string color = defaultColor;

        template<typename T>
        friend std::ostream &operator<<(Logger &log, T op) {
            log.os_ << log.color << op << Logger::defaultColor;
            return log.os_;
        }

        std::ostream &os_;
    };
}

#endif
