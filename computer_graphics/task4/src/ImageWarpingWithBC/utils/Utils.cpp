#include "Utils.h"
#include "Constants.h"
#include "../core/Triangle.h"

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

