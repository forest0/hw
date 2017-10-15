#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "Constants.h"

/* some utility functions
 */
class Utils {
    public:
        static std::string getCurrentTimeString();
        static std::string toString(FigureType type);
};

#endif
