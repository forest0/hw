#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "Constants.h"

class Utils {
    public:
        static std::string getCurrentTimeString();
        static std::string toString(FigureType type);
};

#endif
