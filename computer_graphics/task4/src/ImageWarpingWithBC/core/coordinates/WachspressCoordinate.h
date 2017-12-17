#ifndef WACHSPRESSCOORDINATE_H
#define WACHSPRESSCOORDINATE_H

#include "BarycentricCoordinate.h"

class WachspressCoordinate : public BarycentricCoordinate {
public:
    WachspressCoordinate(std::vector<QPointF> &basePoints);
    virtual ~WachspressCoordinate();
    virtual std::vector<double> getCoordinateOf(
            const QPointF &point) const override;
    virtual double gernateFunction(double r) const override;
private:
    std::vector<double> getTriangleCoordinateOf(
            const QPointF &point) const;
    
};

#endif /* WACHSPRESSCOORDINATE_H */
