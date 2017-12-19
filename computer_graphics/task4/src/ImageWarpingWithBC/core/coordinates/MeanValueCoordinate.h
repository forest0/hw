#ifndef MEANVALUECOORDINATE_H
#define MEANVALUECOORDINATE_H

#include "BarycentricCoordinate.h"

class MeanValueCoordinate : public BarycentricCoordinate {

public:
    MeanValueCoordinate(const std::vector<QPointF> &basePoints);
    MeanValueCoordinate(const std::vector<QPoint> &basePoints);
    void setBasePoints(const std::vector<QPointF> &basePoints);
    virtual std::vector<double> getCoordinateOf(
            const QPointF &point) const override;
    virtual std::vector<double> getCoordinateOf(
            const cv::Point2f &point) const override;
    virtual QPoint getRealCoordinateOf(
            const std::vector<double> &bc) const override;
    virtual double gernateFunction(double r) const override;
    virtual ~MeanValueCoordinate();

private:
    
};

#endif /* MEANVALUECOORDINATE_H */
