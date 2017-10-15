#include "Line.h"
#include "Constants.h"

Line::Line() :
    Figure(), QLine()
{
    type = FigureType::line;
}

Line::Line(const QPoint &point1, const QPoint &point2) :
    Figure(), QLine(point1, point2)
{
    type = FigureType::line;

}

Line::~Line() {

}
void Line::drawWith(QPainter *painter) const {
    painter->drawLine(*this);
}
