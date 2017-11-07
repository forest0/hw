#include "IDWMapper.h"
#include <cmath>
#include "../tools/Log.h"

IDWMapper::IDWMapper(
        const std::vector<std::pair<QPoint, QPoint>> &controlPoints) 
    : Mapper()
{
    // copy control points
    for (const auto &pair : controlPoints) {
        headOfControlPoints.push_back(pair.first);
        tailOfControlPoints.push_back(pair.second);
    }

    this->u = 2.0;
}

IDWMapper::~IDWMapper() {

}

QPoint IDWMapper::map(const QPoint &point) const {

    QPoint targetPoint = QPoint(0,0);
    for (size_t i = 0; i < headOfControlPoints.size(); ++i) {
        targetPoint.rx() += (fi_func(point, i).x() * wi_func(point, i));
        targetPoint.ry() += (fi_func(point, i).y() * wi_func(point, i));
    }
    return targetPoint;
}

double IDWMapper::wi_func(const QPoint &p, int idx) const {
    if (p == this->headOfControlPoints[idx]) {
        return 1;
    } else if (isControlPoint(p)) {
        return 0;
    }

    double sum = 0.0;
    for (const auto &point : headOfControlPoints) {
        sum += delta(p, point);
    }

    return delta(p, headOfControlPoints[idx]) / sum;

}

double IDWMapper::delta(const QPoint &p, const QPoint &pi) const {
    try {

        return std::pow(1.0/distance(p, pi), this->u/2.0);

    } catch (std::exception e) {
        Log::e(e.what());
    }
}

double IDWMapper::distance(const QPoint &p, const QPoint &pi) const {
    return std::sqrt((double)
        (p.x()-pi.x())*(p.x()-pi.x()) + (p.y()-pi.y())*(p.y()-pi.y()));
}

QPoint IDWMapper::fi_func(const QPoint &p, int idx) const {
    double x = tailOfControlPoints[idx].x();
    double y = tailOfControlPoints[idx].y();

    x += (p.x() - headOfControlPoints[idx].x());
    y += (p.y() - headOfControlPoints[idx].y());

    return QPoint((int)x, (int)y);
}

bool IDWMapper::isControlPoint(const QPoint &p) const {
    for (const auto &point : headOfControlPoints) {
        if (point == p) {
            return true;
        }
    }
    return false;
}
