#ifndef  LOG_H
#define LOG_H

#include <string>

class Log {

    public:
        static bool debugOn;

        static void i(const std::string &str);
        static void w(const std::string &str);
        static void e(const std::string &str);

};

#endif
