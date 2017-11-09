#ifndef IDWMAPPER_H
#define IDWMAPPER_H

#include "Mapper.h"

class IDWMapper : public Mapper {
    public:
        IDWMapper(const std::vector<std::pair<QPoint, QPoint>> &controlPoints);
        ~IDWMapper();
        QPoint map(const QPoint &point) const override;

    private:
        double wi_func(const QPoint &p, int idx) const;
        double delta(const QPoint &p, const QPoint &pi) const;
        double distance(const QPoint &p, const QPoint &pi) const;
        QPoint fi_func(const QPoint &p, int idx) const;
        bool isControlPoint(const QPoint &p) const;

    private:
        double u;
        std::vector<QPoint> headOfControlPoints;
        std::vector<QPoint> tailOfControlPoints;
};

#endif // IDWMAPPER_H
