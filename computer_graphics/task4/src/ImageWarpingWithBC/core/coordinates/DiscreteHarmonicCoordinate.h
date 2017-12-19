#ifndef DISCRETEHARMONICCOORDINATE_H
#define DISCRETEHARMONICCOORDINATE_H

#include "BarycentricCoordinate.h"

class DiscreteHarmonicCoordinate : public BarycentricCoordinate {

public:
    DiscreteHarmonicCoordinate(const std::vector<QPointF> &basePoints);
    DiscreteHarmonicCoordinate(const std::vector<QPoint> &basePoints);
    virtual ~DiscreteHarmonicCoordinate();
    virtual std::vector<double> getCoordinateOf(
            const QPointF &point) const override;
    virtual std::vector<double> getCoordinateOf(
            const cv::Point2f &point) const override;
    virtual QPoint getRealCoordinateOf(
            const std::vector<double> &bc) const override;
    virtual double gernateFunction(double r) const override;

private:
    
};

#endif /* DISCRETEHARMONICCOORDINATE_H */
