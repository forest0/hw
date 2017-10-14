#include "Line.h"
#include "Constants.h"

Line::Line() :
    Figure(), QLine()
{
    type = FigureType::line;
}

Line::Line(int x1, int y1, int x2, int y2) :
    Figure(), QLine(x1, y1, x2, y2)
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
