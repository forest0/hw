#ifndef  LOG_H
#define LOG_H

#include <string>

// a logger
class Log {

    public:
        static bool debugOn;

        static void i(const std::string &str); // info
        static void w(const std::string &str); // warning
        static void e(const std::string &str); // error

};

#endif
