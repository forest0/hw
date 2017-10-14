#include "Polygon.h"

Polygon::Polygon(const QVector<QPoint> &points) :
    Figure(), points(points)
{
    type = FigureType::polygon;
}

Polygon::~Polygon() {

}

void Polygon::drawWith(QPainter *painter) const {
    for (int i=0; i < points.size()-1; ++i) {
        painter->drawLine(points[i], points[i+1]);
    }
    painter->drawLine(points.back(), points.front());
}
