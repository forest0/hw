#include "Triangle.h"
#include "../../utils/Constants.h"
#include "../../utils/Utils.h"
#include <iostream>
#include <cassert>

Triangle::Triangle(const cv::Point2f & point1, 
        const cv::Point2f & point2, const cv::Point2f & point3) 
    : point1(point1), point2(point2), point3(point3)
{

}

Triangle::Triangle(const QPointF & point1, 
        const QPointF & point2, const QPointF & point3) 
    : point1(point1.x(), point1.y()), 
      point2(point2.x(), point2.y()), 
      point3(point3.x(), point3.y())
{

}

Triangle::~Triangle() {

}

std::vector<QPoint> Triangle::getInternalIntegerPoints() const {

    std::vector<cv::Point2f> orderedPoints = 
        this->getVerticesByXAscent();

    if (orderedPoints[0].x == orderedPoints[1].x) {
        return this->getInternalIntegerPoints(2);
    } else if (orderedPoints[1].x == orderedPoints[2].x) {
        return this->getInternalIntegerPoints(0);
    } else {

        std::vector<QPoint> result;

        cv::Point2f delta = orderedPoints[2] - orderedPoints[0];
        if (std::abs(delta.x) < Constants::EPSILON) {
            std::cerr << "invalid slope" << std::endl;
            return result;
        }
        float k = delta.y / delta.x;
        float b = orderedPoints[0].y - orderedPoints[0].x*k;
        cv::Point2f dividePoint(orderedPoints[1].x,
                k*orderedPoints[1].x+b);

        std::vector<QPoint> leftPart = Triangle(
                orderedPoints[0], orderedPoints[1], dividePoint)
            .getInternalIntegerPoints(0);

        std::vector<QPoint> rightPart = Triangle(
                orderedPoints[2], orderedPoints[1], dividePoint)
            .getInternalIntegerPoints(2);

        result.reserve(leftPart.size() + rightPart.size());
        result.insert(result.end(), leftPart.begin(), 
                leftPart.end());
        result.insert(result.end(), rightPart.begin(), 
                rightPart.end());

        if ((std::ceil(dividePoint.x) - std::floor(dividePoint.x)) <
                Constants::EPSILON) {
            int x = dividePoint.x;
            float lowerY = orderedPoints[1].y;
            float upperY = dividePoint.y;
            if (lowerY > upperY) {
                std::swap(lowerY, upperY);
            }
            int lowerBound = std::ceil(lowerY);
            int upperBound = std::floor(upperY);
            for (int y = lowerBound + 1; y < upperBound; ++y) {
                result.push_back(QPoint(x, y));
            }

            QPoint lowerPoint(x, lowerBound);
            if (!(this->hasEdgePass(lowerPoint))) {
                result.push_back(lowerPoint);
            }

            if (upperBound > lowerBound) {
                QPoint upperPoint(x, upperBound);
                if (!(this->hasEdgePass(upperPoint))) {
                    result.push_back(upperPoint);
                }
            }

        }

        return result;
    }
}


double Triangle::getArea() const {
    double det = point2.x*point3.y - point3.x*point2.y
        + point3.x*point1.y - point1.x*point3.y
        + point1.x*point2.y - point2.x*point1.y;
    return std::abs(det / 2);
}

std::vector<cv::Point2f> Triangle::getVerticesByXAscent() const {
    std::vector<cv::Point2f> result;
    result.push_back(point1);
    result.push_back(point2);
    result.push_back(point3);

    // bubble sort on y
    if (result[0].x > result[1].x) {
        std::swap(result[0], result[1]);
    }
    if (result[1].x > result[2].x) {
        std::swap(result[1], result[2]);
    }
    if (result[0].x > result[1].x) {
        std::swap(result[0], result[1]);
    }

    // if exist same x, then sort on y
    if ((result[0].x == result[1].x) &&
            (result[0].y > result[1].y)) {
        std::swap(result[0], result[1]);
    }
    if ((result[1].x == result[2].x) &&
            (result[1].y > result[2].y)) {
        std::swap(result[1], result[2]);
    }

    return result;
}

std::vector<QPoint> Triangle::getInternalIntegerPoints(int idx) 
    const {

    assert((0 <= idx) && (idx <= 2));

    int idxArr[2] = {0,0};
    for (int i = 0, index = 0; i < 3; ++i) {
        if (i == idx) {
            continue;
        }
        idxArr[index++] = i;
    }

    std::vector<cv::Point2f> orderedPoints = 
        this->getVerticesByXAscent();

    std::vector<QPoint> result;

    int leftBound  = std::ceil(orderedPoints[0].x);
    // if ((leftBound - orderedPoints[0].x) < Constants::EPSILON) {
    //     leftBound = std::floor(orderedPoints[0].x+1);
    // }
    int rightBound = std::floor(orderedPoints[2].x);
    // if ((orderedPoints[2].x - rightBound) < Constants::EPSILON) {
    //     rightBound = std::ceil(orderedPoints[2].x-1);
    // }

    float k[2] = {0.0f, 0.0f};
    float b[2] = {0.0f, 0.0f};
    cv::Point2f delta;
    for (int i = 0; i < 2; ++i) {
        delta = orderedPoints[idx] - orderedPoints[idxArr[i]];
        if (std::abs(delta.x) < Constants::EPSILON) {
            std::cerr << "invalid slope" << std::endl;
            return result;
        }
        k[i] = delta.y / delta.x;
        b[i] = orderedPoints[idx].y - k[i]*orderedPoints[idx].x;
    }

    if (k[0]*(leftBound+1)+b[0] > k[1]*(leftBound+1)+b[1]) {
        std::swap(k[0], k[1]);
        std::swap(b[0], b[1]);
    }

    int lowerBound = 0;
    int upperBound = 0;
    for (int x = leftBound; x <= rightBound; ++x) {
        lowerBound =  std::ceil(k[0]*x + b[0]);
        upperBound = std::floor(k[1]*x + b[1]);

        if (lowerBound > upperBound) {
            continue;
        }
        
        // for (int y = lowerBound+1; y < upperBound; ++y) {
        //     result.push_back(QPoint(x, y));
        // }
        for (int y = lowerBound; y <= upperBound; ++y) {
            result.push_back(QPoint(x, y));
        }

        // QPoint lowerPoint(x, lowerBound);
        // if (!(this->hasEdgePass(lowerPoint))) {
        //     result.push_back(lowerPoint);
        // }
        // if (upperBound > lowerBound) {
        //     QPoint upperPoint(x, upperBound);
        //     if (!(this->hasEdgePass(upperPoint))) {
        //         result.push_back(upperPoint);
        //     }
        // }

    }

    return result;
}
bool Triangle::hasEdgePass(const QPointF & point) const {
    cv::Point2f thePoint = Utils::qPointF2cvPoint2f(point);
    Triangle triangle(thePoint, point1, point2);
    if (triangle.getArea() < Constants::EPSILON) {
        return true;
    }

    triangle = Triangle(thePoint, point1, point3);
    if (triangle.getArea() < Constants::EPSILON) {
        return true;
    }

    triangle = Triangle(thePoint, point2, point3);
    if (triangle.getArea() < Constants::EPSILON) {
        return true;
    }

    return false;
}
