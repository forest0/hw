#include "Utils.h"
#include "Constants.h"
#include "../core/model/Triangle.h"
#include <cstdlib>
#include <ctime>
#include <cassert>

Utils::Utils() {

}

Utils::~Utils() {

}

QPointF Utils::cvPoint2f2QPointF(const cv::Point2f &point) {
    return QPointF(point.x, point.y);
}

cv::Point2f Utils::qPointF2cvPoint2f(const QPointF &point) {
    return cv::Point2f(point.x(), point.y());
}

bool Utils::isOnSameLine(const QPointF & point1, 
        const QPointF & point2, const QPointF & point3) {

    return (Triangle(point1, point2, point3).getArea()
            < Constants::EPSILON);
}

void Utils::initSeed() {
    static bool isSeedInitialized = false;
    if (!isSeedInitialized) {
        std::srand((unsigned) std::time(nullptr));
        isSeedInitialized = true;
    }
}

std::vector<double> Utils::getRandomBC(int dimension) {
    assert(dimension > 0);
    initSeed();
    std::vector<double> bc(dimension);

    double sum = 0.0;
    for (int i = 0; i < dimension; ++i) {
        bc[i] = std::rand() % (RAND_MAX);
        sum += bc[i];
    }
    assert(sum > Constants::EPSILON);
    for (int i = 0; i < dimension; ++i) {
        bc[i] /= sum;
    }
    return bc;
}

