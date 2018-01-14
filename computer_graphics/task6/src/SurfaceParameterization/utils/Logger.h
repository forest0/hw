#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <stdio.h>
#include "Utils.h"

enum class LogLevel {
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR,
    SILENCE
};

// a logger
class Logger {

public:

    template <typename... Args>
    static void d(const char *format, Args... args) {
        printLog(LogLevel::DEBUG, format, args...);
    }

    template <typename... Args>
    static void i(const char *format, Args... args) {
        printLog(LogLevel::INFO, format, args...);
    }

    template <typename... Args>
    static void w(const char *format, Args... args) {
        printLog(LogLevel::WARNING, format, args...);
    }

    template <typename... Args>
    static void e(const char *format, Args... args) {
        printLog(LogLevel::ERROR, format, args...);
    }

private:

#define LOG_FILE_DESCRIPTOR stderr
    static const LogLevel currentLogLevel = LogLevel::DEBUG;

    static void printHeader(const LogLevel &level) {
        const char *levelStr = nullptr;
        switch (level) {
            case LogLevel::DEBUG:
                levelStr = "[DEBUG]";
                break;
            case LogLevel::INFO:
                levelStr = "[INFO]";
                break;
            case LogLevel::WARNING:
                levelStr = "[WARNING]";
                break;
            case LogLevel::ERROR:
                levelStr = "[ERROR]";
                break;
            case LogLevel::SILENCE:
                // no log should be output
                levelStr = "[SILENCE]";
                break;
        }
        fprintf(LOG_FILE_DESCRIPTOR, "%s %s: ",
                Utils::getCurrentTimeString().c_str(), levelStr);
    }

    template <typename... Args>
    static void printLog(const LogLevel &level, const char *format,
            Args...args) {

        if (currentLogLevel <= level) {
            printHeader(level);
            fprintf(LOG_FILE_DESCRIPTOR, format, args...);
        }
    }

};

#undef LOG_FILE_DESCRIPTOR
#endif
