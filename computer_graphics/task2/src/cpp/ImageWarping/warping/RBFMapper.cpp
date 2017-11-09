#include "RBFMapper.h"
#include <cmath>
#include <limits>
#include <iostream>

RBFMapper::RBFMapper(
        const std::vector<std::pair<QPoint, QPoint>> &controlPoints)
    : Mapper(), A(controlPoints.size(), controlPoints.size()),
    b(controlPoints.size(),2), alphai(controlPoints.size(), 2)
{
    for (const auto &pair : controlPoints) {
        headOfControlPoints.push_back(pair.first);
        tailOfControlPoints.push_back(pair.second);
    }

    this->u = 1;

    calculate_ri();

    init_A();
    init_b();
    calculate_alphai();

}

RBFMapper::~RBFMapper() {

}

QPoint RBFMapper::map(const QPoint &point) const {

    double x = point.x();
    double y = point.y();
    for (size_t i = 0; i < headOfControlPoints.size(); ++i) {
        x += fi_func(point, i)*alphai(i,0);
        y += fi_func(point, i)*alphai(i,1);
    }
    return QPoint((int)x, (int)y);
}

void RBFMapper::calculate_ri() {
    for (size_t i = 0; i< headOfControlPoints.size(); ++i) {
        double minDistance = std::numeric_limits<double>::max();
        for (size_t j = 0; j < headOfControlPoints.size(); ++j) {
            if (i != j) {
                double d = distance(headOfControlPoints[i], 
                        headOfControlPoints[j]);
                if (d < minDistance) {
                    minDistance = d;
                }
            }
        }
        ri.push_back(minDistance);
    }
}

double RBFMapper::distance(const QPoint &pointA, const QPoint &pointB) const {
    return std::sqrt((pointA.x()-pointB.x())*(pointA.x()-pointB.x())
            + (pointA.y()-pointB.y())*(pointA.y()-pointB.y()));
}

double RBFMapper::fi_func(const QPoint &p, int idx) const {
    double dis = distance(p, headOfControlPoints[idx]);
    return std::pow(dis*dis+ri[idx]*ri[idx], u/2.0);
}

void RBFMapper::init_b() {
    for (size_t i = 0; i < headOfControlPoints.size(); ++i) {
        b(i, 0) = tailOfControlPoints[i].x() - headOfControlPoints[i].x();
        b(i, 1) = tailOfControlPoints[i].y() - headOfControlPoints[i].y();
    }
}

void RBFMapper::init_A() {
    for (size_t i = 0; i < headOfControlPoints.size(); ++i) {
        for (size_t j = 0; j < headOfControlPoints.size(); ++j) {
            A(i,j) = fi_func(headOfControlPoints[i], j);
        }
    }
}

void RBFMapper::calculate_alphai() {
    // alphai = A.ldlt().solve(b);
    alphai = A.colPivHouseholderQr().solve(b);
}
