#include <chrono>
#include <sstream>
#include <iomanip>
#include "Utils.h"
#include "Log.h"
#include <cassert>
#include <iostream>

#include "../view/ImageView.h"

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

std::vector<std::pair<QPoint, QPoint>> Utils::getControlPoints() {
    std::vector<std::pair<QPoint, QPoint>> controlPoints;
    controlPoints.push_back(std::make_pair(QPoint(0,0), QPoint(50,50)));
    controlPoints.push_back(std::make_pair(QPoint(255,0), QPoint(205,50)));
    controlPoints.push_back(std::make_pair(QPoint(255,255), QPoint(205,205)));
    controlPoints.push_back(std::make_pair(QPoint(0,255), QPoint(50,205)));

    return controlPoints;
}

void Utils::showImage(QImage *image) {
    assert(image);
    ImageView view;
    view.setImage(image);
    view.show();
    view.exec();
}

void Utils::printControlPoints(
    const std::vector<std::pair<QPoint, QPoint>> &controlPoints) {
    Log::i("print control points");
    std::for_each(controlPoints.cbegin(), controlPoints.cend(),
            [](const std::pair<QPoint, QPoint> &pair) {
            Utils::printPoint(pair.first);
            std::cout << " -> ";
            Utils::printPoint(pair.second);
            std::cout << std::endl;
    });
}

void Utils::printPoint(const QPoint &point) {
    std::cout << "(" << point.x() << ","
        << point.y() << ")";
}
