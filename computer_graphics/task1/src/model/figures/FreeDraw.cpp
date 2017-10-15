#include "FreeDraw.h"

FreeDraw::FreeDraw(const QVector<QPoint> &points) :
    Figure(),
    points(points)
{
    type = FigureType::freeDraw;
}

FreeDraw::~FreeDraw() {
    
}
void FreeDraw::drawWith(QPainter *painter) const {
    for (int i = 0; i < points.size()-1; ++i) {
        painter->drawLine(points[i], points[i+1]);
    }
}
