#include "Rectangle.h"

Rectangle::Rectangle() :
    Figure(), QRect()
{
    type = FigureType::rectangle;
}

Rectangle::Rectangle(const QPoint &topLeft, 
        const QPoint &bottomRight) :
    Figure(), QRect(topLeft, bottomRight)
{
    type = FigureType::rectangle;
}

Rectangle::~Rectangle() {

}

void Rectangle::drawWith(QPainter *painter) const {
    painter->drawRect(*this);
}
