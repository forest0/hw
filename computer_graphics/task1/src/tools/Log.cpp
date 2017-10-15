#include <iostream>
#include "Log.h"
#include "Utils.h"

#ifndef NDEBUG
    bool Log::debugOn = true;
#else
    bool Log::debugOn = false;
#endif

static void printHeader(const std::string &msgType) {
    std::cerr << Utils::getCurrentTimeString() << " "
        << msgType << ": ";
}

static void printLog(const std::string &msgType, 
        const std::string &msg) {

    if (Log::debugOn) {
        printHeader(msgType);
        std::cerr << msg << std::endl;
    }
}

void Log::i(const std::string &msg) {
    printLog("[INFO]", msg);
}

void Log::w(const std::string &msg) {
    printLog("[WARNING]", msg);
}

void Log::e(const std::string &msg) {
    printLog("[ERROR]", msg);
}
