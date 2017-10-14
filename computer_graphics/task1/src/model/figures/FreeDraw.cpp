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
    painter->drawLines(points);
}
