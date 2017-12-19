#ifndef WACHSPRESSCOORDINATE_H
#define WACHSPRESSCOORDINATE_H

#include "BarycentricCoordinate.h"
#include <opencv2/core.hpp>

class WachspressCoordinate : public BarycentricCoordinate {
public:
    WachspressCoordinate(std::vector<QPointF> &basePoints);
    WachspressCoordinate(std::vector<QPoint> &basePoints);
    virtual ~WachspressCoordinate();
    virtual std::vector<double> getCoordinateOf(
            const QPointF &point) const override;
    virtual std::vector<double> getCoordinateOf(
            const cv::Point2f &point) const override;
    virtual QPoint getRealCoordinateOf(
            const std::vector<double> &bc) const override;
    virtual double gernateFunction(double r) const override;
private:
    std::vector<double> getTriangleCoordinateOf(
            const QPointF &point) const;
    
};

#endif /* WACHSPRESSCOORDINATE_H */
