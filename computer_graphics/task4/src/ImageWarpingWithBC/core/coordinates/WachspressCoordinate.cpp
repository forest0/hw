#include "WachspressCoordinate.h"
#include "../Triangle.h"
#include "../../utils/Utils.h"
#include "../../utils/Constants.h"
#include <QtCore/QtDebug>
#include <iostream>
#include <cassert>

WachspressCoordinate::WachspressCoordinate(
        std::vector<QPointF> & basePoints) 
    :BarycentricCoordinate(basePoints)
{

}


WachspressCoordinate::~WachspressCoordinate() {

}

static bool assertHelper(const QPointF &point) {
    qDebug() << point << " caused assert failed";
    return false;
}

std::vector<double> WachspressCoordinate::getCoordinateOf(
        const QPointF & point) const {

    // if (basePoints.size() == 3) {
    //     return this->getTriangleCoordinateOf(point);
    // }
    /* TODO:  <17-12-17, make sure every element in coordinate to be zero?> */
    unsigned int size = basePoints.size();
    std::vector<double> coordinate(size);
    
    for (unsigned int i = 0; i < size; ++i) {
        if (basePoints[i] == point) {
            coordinate[i] = 1.0;
            std::cout << "current point is vertex, return!" 
                << std::endl;
            return coordinate;
        }
    }

    int previousIdx = 0;
    int nextIdx = 0;
    double sum = 0.0;
    for (unsigned int i = 0; i < size; ++i) {
        previousIdx = (i-1+size) % size;
        nextIdx = (i+1) % size;

        // qDebug() << basePoints[previousIdx];
        // qDebug() << basePoints[i];
        // qDebug() << basePoints[nextIdx];

        double area1 = Triangle(basePoints[previousIdx],
                basePoints[i], point) .getArea(); // A_{i-1}
        double area2 = Triangle(basePoints[i], 
                basePoints[nextIdx], point).getArea(); // A_i
        // double area3 = Triangle(basePoints[previousIdx],
        //         basePoints[nextIdx], point).getArea(); // B_i
        double area3 = Triangle(basePoints[previousIdx],
            basePoints[i], basePoints[nextIdx]).getArea();

        // std::cout << "area1: " << area1 << std::endl;
        // std::cout << "area2: " << area2 << std::endl;
        // std::cout << "area3: " << area3 << std::endl;

        /* TODO:  <17-12-17, why this general method done not
         *          suit for triangle?> */
        // double w = (area1 - area3 + area2) / (area1 * area2);
        assert((area1 * area2 > Constants::EPSILON) || assertHelper(point));
        double w = (area3) / (area1 * area2);
        sum += w;

        // std::cout << "w: " << w << std::endl;
        // std::cout << "*********************************" << std::endl;


        coordinate[i] = w;
    }

    assert(sum > Constants::EPSILON);

    // std::cout << "sum: " << sum << std::endl;
    // QPointF fitPoint(0.0f, 0.0f);
    for (unsigned int i = 0; i < size; ++i) {
        coordinate[i] /= sum;
        // fitPoint += (coordinate[i]*basePoints[i]);
        // qDebug() << basePoints[i] << "-->" << coordinate[i];
    }

    // qDebug() << "fitPoint: " << fitPoint;

    return coordinate;
}

double WachspressCoordinate::gernateFunction(double r) const {
    return 1.0;
}

std::vector<double> WachspressCoordinate::getTriangleCoordinateOf(
        const QPointF & point) const {

    const unsigned int size = 3;
    assert(basePoints.size() == size);

    std::vector<double> coordinate;

    int previousIdx = 0;
    int nextIdx = 0;
    for (unsigned int i = 0; i < size; ++i) {
        previousIdx = (i-1+size) % size;
        nextIdx = (i+1) % size;

        // qDebug() << basePoints[previousIdx];
        // qDebug() << basePoints[i];
        // qDebug() << basePoints[nextIdx];
        double area1 = Triangle(basePoints[previousIdx],
                basePoints[i], point) .getArea(); // A_{i-1}
        double area2 = Triangle(basePoints[i], 
                basePoints[nextIdx], point).getArea(); // A_i
        double area3 = Triangle(basePoints[previousIdx],
                basePoints[nextIdx], point).getArea(); // B_i

        // std::cout << "area1: " << area1 << std::endl;
        // std::cout << "area2: " << area2 << std::endl;
        // std::cout << "area3: " << area3 << std::endl;

        double w = area3 / (area1 + area2 + area3);

        // std::cout << "w: " << w << std::endl;
        // std::cout << "*********************************" << std::endl;

        coordinate.push_back(w);
    }

    return coordinate;
}

