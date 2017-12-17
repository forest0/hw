#ifndef BARYCENTRICCOORDINATE_H
#define BARYCENTRICCOORDINATE_H

#include <QtCore/QPointF>
#include <vector>

class BarycentricCoordinate {

public:
    BarycentricCoordinate(const std::vector<QPointF> &basePoints);
    void setBasePoints(const std::vector<QPointF> &basePoints);
    virtual std::vector<double> getCoordinateOf(
            const QPointF &point) const = 0;
    virtual double gernateFunction(double r) const = 0;
    virtual ~BarycentricCoordinate();
protected:
    std::vector<QPointF> basePoints;
private:
};

#endif /* BARYCENTRICCOORDINATESYSTEM_H */
