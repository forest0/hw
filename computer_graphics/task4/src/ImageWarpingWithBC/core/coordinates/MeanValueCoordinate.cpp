#include "MeanValueCoordinate.h"
#include "../model/Triangle.h"
#include "../../utils/Constants.h"
#include "../../utils/Utils.h"

MeanValueCoordinate::MeanValueCoordinate(
        const std::vector<QPointF> & basePoints) 
    :BarycentricCoordinate(basePoints)
{

}

MeanValueCoordinate::MeanValueCoordinate(
        const std::vector<QPoint> & basePoints) 
    :BarycentricCoordinate(basePoints)
{

}

MeanValueCoordinate::~MeanValueCoordinate() {

}


void MeanValueCoordinate::setBasePoints(
        const std::vector<QPointF> & basePoints) {

}

std::vector<double> MeanValueCoordinate::getCoordinateOf(
        const QPointF & point) const {

    unsigned int size = basePoints.size();
    std::vector<double> coordinate(size);
    for (unsigned int i = 0; i < size; ++i) {
        coordinate[i] = 0.0;
    }
    
    // if point is one of the basePoints
    for (unsigned int i = 0; i < size; ++i) {
        if (basePoints[i] == point) {
            coordinate[i] = 1.0;
            return coordinate;
        }
    }

    int previousIdx = 0;
    int nextIdx = 0;
    double sum = 0.0;
    for (unsigned int i = 0; i < size; ++i) {
        previousIdx = (i-1+size) % size;
        nextIdx = (i+1) % size;

        double area1 = Triangle(basePoints[previousIdx],
                basePoints[i], point) .getArea(); // A_{i-1}
        double area2 = Triangle(basePoints[i], 
                basePoints[nextIdx], point).getArea(); // A_i
        double area3 = Triangle(basePoints[previousIdx],
                basePoints[nextIdx], point).getArea(); // B_i

        if (area1 < Constants::EPSILON) {
            double lambda = (point.x()-basePoints[i].x()) / 
                (basePoints[previousIdx].x() - basePoints[i].x());

            for (unsigned int j = 0; j < size; ++j) {
                coordinate[j] = 0.0;
            }
            coordinate[previousIdx] = lambda;
            coordinate[i] = 1 - lambda;
            return coordinate;
        }

        if (area2 < Constants::EPSILON) {
            double lambda = (point.x()-basePoints[nextIdx].x()) / 
                (basePoints[i].x() - basePoints[nextIdx].x());

            for (unsigned int j = 0; j < size; ++j) {
                coordinate[j] = 0.0;
            }
            coordinate[i] = lambda;
            coordinate[nextIdx] = 1 - lambda;
            return coordinate;
        }

        double nextC = gernateFunction(
                this->distance(basePoints[nextIdx], point));
        double currentC = gernateFunction(
                this->distance(basePoints[i], point));
        double previousC = gernateFunction(
                this->distance(basePoints[previousIdx], point));
        double w = (nextC*area1 - currentC*area3 + previousC*area2) 
                / (area1 * area2);
        sum += w;


        coordinate[i] = w;
    }

    assert(sum > Constants::EPSILON);

    for (unsigned int i = 0; i < size; ++i) {
        coordinate[i] /= sum;
    }

    return coordinate;

}

std::vector<double> MeanValueCoordinate::getCoordinateOf(
        const cv::Point2f & point) const {
    return this->getCoordinateOf(Utils::cvPoint2f2QPointF(point));

}

QPoint MeanValueCoordinate::getRealCoordinateOf(
        const std::vector<double> & bc) const {
    assert(bc.size() == basePoints.size());
    double x = 0;
    double y = 0;

    for (unsigned int i = 0; i < bc.size(); ++i) {
        x += bc[i]*basePoints[i].x();
        y += bc[i]*basePoints[i].y();
    }

    return QPoint(x,y);

}

double MeanValueCoordinate::gernateFunction(double r) const {
    assert(r > Constants::EPSILON);
    return r;
}

