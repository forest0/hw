#include "BarycentricCoordinate.h"
#include <cmath>

BarycentricCoordinate::BarycentricCoordinate(
        const std::vector<QPointF> &basePoints) 
    :basePoints(basePoints)
{
}

BarycentricCoordinate::BarycentricCoordinate(
        const std::vector<QPoint> &basePoints) 
    :basePoints()
{
    for (const auto &point : basePoints) {
        this->basePoints.push_back(point);
    }
}

void BarycentricCoordinate::setBasePoints(
        const std::vector<QPointF> &basePoints) {
    this->basePoints = basePoints;
}

BarycentricCoordinate::~BarycentricCoordinate() {

}

double BarycentricCoordinate::distance(const QPointF & point1, 
        const QPointF & point2) const {
    return std::sqrt((point1.x()-point2.x())*(point1.x()-point2.x()) 
            + (point1.y()-point2.y())*(point1.y()-point2.y()));
}

