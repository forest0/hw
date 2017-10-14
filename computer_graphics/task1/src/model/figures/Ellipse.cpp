#include "Ellipse.h"

Ellipse::Ellipse(const QPoint &topLeft, const QPoint &bottomRight) :
    Figure(),
    topLeft(topLeft), bottomRight(bottomRight)
    
{
    type = FigureType::ellipse;
}

Ellipse::~Ellipse() {

}

void Ellipse::drawWith(QPainter *painter) const {
    painter->drawEllipse(QRect(topLeft, bottomRight));
}
