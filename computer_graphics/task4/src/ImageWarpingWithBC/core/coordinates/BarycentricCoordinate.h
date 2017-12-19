#ifndef BARYCENTRICCOORDINATE_H
#define BARYCENTRICCOORDINATE_H

#include <QtCore/QPointF>
#include <vector>
#include <opencv2/core.hpp>

class BarycentricCoordinate {

public:
    BarycentricCoordinate(const std::vector<QPointF> &basePoints);
    BarycentricCoordinate(const std::vector<QPoint> &basePoints);
    void setBasePoints(const std::vector<QPointF> &basePoints);
    virtual std::vector<double> getCoordinateOf(
            const QPointF &point) const = 0;
    virtual std::vector<double> getCoordinateOf(
            const cv::Point2f &point) const = 0;
    virtual QPoint getRealCoordinateOf(
            const std::vector<double> &bc) const = 0;
    virtual double gernateFunction(double r) const = 0;
    virtual ~BarycentricCoordinate();
    double distance(const QPointF &point1, const QPointF &point2) const;
protected:
    std::vector<QPointF> basePoints;
private:
};

#endif /* BARYCENTRICCOORDINATESYSTEM_H */
