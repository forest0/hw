#include <chrono>
#include <sstream>
#include <iomanip>
#include "Utils.h"
#include "Log.h"

std::string Utils::getCurrentTimeString() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch() % std::chrono::seconds(1)).count();
    std::stringstream ss;
    // std::localtime may cause data races
    ss << std::put_time(std::localtime(&now_c), "%T") << "."
        << std::setw(3) << std::setfill('0') << ms;
    return ss.str();
}

std::string Utils::toString(FigureType type) {
    switch(type) {
        case FigureType::line:
            return "line";
        case FigureType::rectangle:
            return "rectangle";
        case FigureType::polygon:
            return "polygon";
        case FigureType::ellipse:
            return "ellipse";
        case FigureType::freeDraw:
            return "freeDraw";
        default:
            Log::e("invalid figure type");
            return "";
    }
}
