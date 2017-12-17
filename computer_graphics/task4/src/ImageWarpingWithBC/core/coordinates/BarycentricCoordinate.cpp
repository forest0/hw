#include "BarycentricCoordinate.h"

BarycentricCoordinate::BarycentricCoordinate(
        const std::vector<QPointF> &basePoints) 
    :basePoints(basePoints)
{
}

void BarycentricCoordinate::setBasePoints(
        const std::vector<QPointF> &basePoints) {
    this->basePoints = basePoints;
}

BarycentricCoordinate::~BarycentricCoordinate() {

}

